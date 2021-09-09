#pragma once

#include <Windows.h>

#include <Platform/Render/GLContext/GLContext.h>
#include <Platform/Window/Win32WindowHandle.h>

namespace TE
{
    class WGLContext : public GLContext
    {
    public:
        WGLContext(WindowHandle *windowHandle);
        ~WGLContext();
        bool Init(int openGLMajorVersion, int openGLMinorVersion);

        void SetSwapInterval(int interval);
        void ProcessSwapChain();

    private:
        bool InitExtensions();
        bool BindExtensions();

        Win32WindowHandle *_windowHandle;
        HDC _displayContext;
        HGLRC _renderContext;
    };
}