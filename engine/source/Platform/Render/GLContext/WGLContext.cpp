#include <format>
#include <GL/gl3w.h>
#include <GL/wglext.h>

#include <Core/Logger.h>
#include <Platform/Render/GLContext/WGLContext.h>

namespace TE
{
    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = nullptr;

    WGLContext::WGLContext(const WindowHandle * const windowHandle)
    {
        Logger::Message("GLContext: WGLContext");

        _windowHandle = dynamic_cast<const Win32WindowHandle * const>(windowHandle);
    }

    WGLContext::~WGLContext()
    {
        Logger::Message("GLContext: destroy");

        HWND hWindow = static_cast<HWND>(_windowHandle->GetRawHandle());

        wglDeleteContext(_renderContext);
        ReleaseDC(hWindow, _displayContext);
    }

    bool WGLContext::Init(int openGLMajorVersion, int openGLMinorVersion)
    {
        Logger::Message("GLContext: init");

        if (!InitExtensions())
        {
            return false;
        }

        if (!gl3wIsSupported(openGLMajorVersion, openGLMinorVersion))
        {
            Logger::Message(std::format("GLContext: OpenGL version {}.{} is not supported", openGLMajorVersion, openGLMinorVersion), Logger::Error);
            return false;
        }

        HWND hWindow = static_cast<HWND>(_windowHandle->GetRawHandle());
        _displayContext = GetDC(hWindow);
        if (!_displayContext)
        {
            Logger::Message(std::format("GLContext: window display context fail {}", GetLastError()), Logger::Error);
            return false;
        }

        const int pixelFormatAttributes[] =
                {
                        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
                        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
                        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
                        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
                        WGL_COLOR_BITS_ARB, 32,
                        WGL_DEPTH_BITS_ARB, 24,
                        WGL_ALPHA_BITS_ARB, 8,
                        WGL_STENCIL_BITS_ARB, 8,
                        WGL_SAMPLES_ARB, 4,
                        WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
                        0
                };
        int contextAttributes[] =
                {
                        WGL_CONTEXT_MAJOR_VERSION_ARB, openGLMajorVersion,
                        WGL_CONTEXT_MINOR_VERSION_ARB, openGLMinorVersion,
                        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                        0
                };

        int pixelFormat;
        uint32_t formatCount;
        if (!wglChoosePixelFormatARB(_displayContext, pixelFormatAttributes, nullptr, 1, &pixelFormat, &formatCount))
        {
            Logger::Message(std::format("GLContext: choose pixel format fail {}", GetLastError()), Logger::Error);
            return false;
        }

        if (formatCount == 0)
        {
            Logger::Message(std::format("GLContext: pixel format not found {}", GetLastError()), Logger::Error);
            return false;
        }

        PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
        if (!DescribePixelFormat(_displayContext, pixelFormat, sizeof(pixelFormatDescriptor), &pixelFormatDescriptor))
        {
            Logger::Message(std::format("GLContext: pixel format validation fail {}", GetLastError()), Logger::Error);
            return false;
        }

        if (!SetPixelFormat(_displayContext, pixelFormat, &pixelFormatDescriptor))
        {
            Logger::Message(std::format("GLContext: set pixel format fail {}", GetLastError()), Logger::Error);
            return false;
        }

        _renderContext = wglCreateContextAttribsARB(_displayContext, nullptr, contextAttributes);
        if (!_renderContext)
        {
            Logger::Message(std::format("GLContext: context creation fail {}", GetLastError()), Logger::Error);
            return false;
        }

        if (!wglMakeCurrent(_displayContext, _renderContext))
        {
            Logger::Message(std::format("GLContext: context setup fail {}", GetLastError()), Logger::Error);
            return false;
        }

        Logger::Message(std::format("GLContext: {} {}", (const char *)glGetString(GL_VENDOR), (const char *)glGetString(GL_VERSION)), Logger::Info);

        return true;
    }

    void WGLContext::SetSwapInterval(int interval)
    {
        wglSwapIntervalEXT(interval);
    }

    void WGLContext::ProcessSwapChain()
    {
        SwapBuffers(_displayContext);
    }

    bool WGLContext::InitExtensions()
    {
        std::wstring tempClassName = L"te_ext";

        HMODULE hInstance = GetModuleHandle(nullptr);

        WNDCLASSEX windowClass;
        ZeroMemory(&windowClass, sizeof(windowClass));
        windowClass.cbSize = sizeof(windowClass);
        windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        windowClass.lpfnWndProc = DefWindowProc;
        windowClass.hInstance = hInstance;
        windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        windowClass.lpszClassName = tempClassName.c_str();

        if (!RegisterClassEx(&windowClass))
        {
            Logger::Message(std::format("GLContext: [ext] window class fail {}", GetLastError()), Logger::Error);
            return false;
        }

        HWND tempExtensionWindow = CreateWindow(
                tempClassName.c_str(),
                nullptr,
                WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                0, 0, 0, 0,
                nullptr, nullptr, hInstance, nullptr);

        if (!tempExtensionWindow)
        {
            Logger::Message(std::format("GLContext: [ext] window init fail {}", GetLastError()), Logger::Error);
            return false;
        }

        HDC tempDisplayContext = GetDC(tempExtensionWindow);
        if (!tempDisplayContext)
        {
            Logger::Message(std::format("GLContext: [ext] window display context fail {}", GetLastError()), Logger::Error);
            return false;
        }

        PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
        memset(&pixelFormatDescriptor, 0, sizeof(PIXELFORMATDESCRIPTOR));
        pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pixelFormatDescriptor.nVersion = 1;
        pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
        pixelFormatDescriptor.cColorBits = 32;
        pixelFormatDescriptor.cDepthBits = 24;
        pixelFormatDescriptor.cAlphaBits = 8;
        pixelFormatDescriptor.cStencilBits = 8;

        int pixelFormat = ChoosePixelFormat(tempDisplayContext, &pixelFormatDescriptor);
        if (pixelFormat == 0)
        {
            Logger::Message(std::format("GLContext: [ext] choose pixel format fail {}", GetLastError()), Logger::Error);
            return false;
        }

        if (!DescribePixelFormat(tempDisplayContext, pixelFormat, sizeof(pixelFormatDescriptor), &pixelFormatDescriptor))
        {
            Logger::Message(std::format("GLContext: [ext] pixel format validation fail {}", GetLastError()), Logger::Error);
            return false;
        }

        if (!SetPixelFormat(tempDisplayContext, pixelFormat, &pixelFormatDescriptor))
        {
            Logger::Message(std::format("GLContext: [ext] set pixel format fail {}", GetLastError()), Logger::Error);
            return false;
        }

        HGLRC tempRenderContext = wglCreateContext(tempDisplayContext);
        if (!tempRenderContext)
        {
            Logger::Message(std::format("GLContext: [ext] context creation fail {}", GetLastError()), Logger::Error);
            return false;
        }

        if (!wglMakeCurrent(tempDisplayContext, tempRenderContext))
        {
            Logger::Message(std::format("GLContext: [ext] context setup fail {}", GetLastError()), Logger::Error);
            return false;
        }

        if (!BindExtensions())
        {
            Logger::Message("GLContext: [ext] extension bind fail", Logger::Error);
            return false;
        }

        wglDeleteContext(tempRenderContext);
        ReleaseDC(tempExtensionWindow, tempDisplayContext);
        DestroyWindow(tempExtensionWindow);
        UnregisterClass(tempClassName.c_str(), hInstance);

        return true;
    }

    bool WGLContext::BindExtensions()
    {
        gl3wInit();

        wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)(gl3wGetProcAddress("wglChoosePixelFormatARB"));
        if (!wglChoosePixelFormatARB)
        {
            Logger::Message("GLContext: [ext bind] wglChoosePixelFormatARB fail", Logger::Error);
            return false;
        }

        wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)(gl3wGetProcAddress("wglCreateContextAttribsARB"));
        if (!wglCreateContextAttribsARB)
        {
            Logger::Message("GLContext: [ext bind] wglCreateContextAttribsARB fail", Logger::Error);
            return false;
        }

        wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)(gl3wGetProcAddress("wglSwapIntervalEXT"));
        if (!wglSwapIntervalEXT)
        {
            Logger::Message("GLContext: [ext bind] wglSwapIntervalEXT fail", Logger::Error);
            return false;
        }

        return true;
    }
}