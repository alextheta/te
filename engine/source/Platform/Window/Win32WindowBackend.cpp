#include <Windows.h>
#include <format>

#include <Core/Logger.h>
#include <Platform/Window/Win32WindowBackend.h>

namespace TE
{
    const std::wstring WindowClassName(L"te_window_class");

    Win32WindowBackend::Win32WindowBackend()
    {
        Logger::Message("WindowBackend: Win32WindowBackend");
    }

    Win32WindowBackend::~Win32WindowBackend()
    {
        Logger::Message("Win32WindowBackend: destroy");

        HWND hWindow = static_cast<HWND>(GetWindowHandle()->GetRawHandle());
        HMODULE hInstance = GetModuleHandle(nullptr);

        DestroyWindow(hWindow);
        UnregisterClass(WindowClassName.c_str(), hInstance);
    }

    bool Win32WindowBackend::Init(WindowSettings &windowSettings)
    {
        Logger::Message("WindowBackend: init");

        _windowHandle = std::unique_ptr<WindowHandle>(MakeWindow(windowSettings));
        if (!_windowHandle)
        {
            Logger::Message("WindowBackend: window init fail", Logger::Error);
            return false;
        }

        return true;
    }

    void Win32WindowBackend::PollEvents()
    {
        MSG msg;
        PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    void Win32WindowBackend::Show()
    {
        ShowWindow(static_cast<HWND>(_windowHandle->GetRawHandle()), SW_SHOW);
    }

    void Win32WindowBackend::OverrideWindowProcedure(LRESULT (*WindowProcedurePointer)(HWND hWnd, unsigned int msg, WPARAM wparam, LPARAM lparam))
    {
        WindowProcedureOverride = WindowProcedurePointer;
    }

    LRESULT Win32WindowBackend::WindowProcedure(HWND hWnd, unsigned int msg, WPARAM wparam, LPARAM lparam)
    {
        switch (msg)
        {
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            case WM_CLOSE:
                WindowCloseEvent();
                DestroyWindow(hWnd);
                break;
            case WM_SIZE:
                WindowResizeEvent(LOWORD(lparam), HIWORD(lparam));
                break;
            default:
                if (WindowProcedureOverride != nullptr && WindowProcedureOverride(hWnd, msg, wparam, lparam))
                {
                    return true;
                }
                return DefWindowProc(hWnd, msg, wparam, lparam);
        }
        return 0;
    }

    Win32WindowHandle *const Win32WindowBackend::MakeWindow(WindowSettings &windowSettings)
    {
        HMODULE hInstance = GetModuleHandle(nullptr);
        if (!hInstance)
        {
            Logger::Message(std::format("WindowBackend: instance handle is null {}", GetLastError()), Logger::Error);
            return nullptr;
        }

        WNDCLASSEX windowClass;
        memset(&windowClass, 0, sizeof(WNDCLASSEX));
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.style = CS_DBLCLKS;
        windowClass.lpfnWndProc = (WNDPROC) WindowProcedure;
        windowClass.cbClsExtra = 0;
        windowClass.cbWndExtra = 0;
        windowClass.hInstance = hInstance;
        windowClass.hIcon = ::LoadIcon(nullptr, IDI_APPLICATION);
        windowClass.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
        windowClass.hbrBackground = ::CreateSolidBrush(COLOR_WINDOW + 1);
        windowClass.lpszMenuName = nullptr;
        windowClass.lpszClassName = WindowClassName.c_str();
        windowClass.hIconSm = nullptr;

        if (!RegisterClassEx(&windowClass))
        {
            Logger::Message(std::format("WindowBackend: class registration fail {}", GetLastError()), Logger::Error);
            return nullptr;
        }

        RECT desktopRect;
        if (!GetWindowRect(GetDesktopWindow(), &desktopRect))
        {
            Logger::Message(std::format("WindowBackend: desktop rect obtain fail {}", GetLastError()), Logger::Error);
            return nullptr;
        }

        auto x = (desktopRect.right / 2) - (windowSettings.width / 2);
        auto y = (desktopRect.bottom / 2) - (windowSettings.height / 2);

        RECT adjustedWindowRect;
        adjustedWindowRect.left = x;
        adjustedWindowRect.top = y;
        adjustedWindowRect.right = x + windowSettings.width;
        adjustedWindowRect.bottom = y + windowSettings.height;

        AdjustWindowRectEx(&adjustedWindowRect, WS_OVERLAPPEDWINDOW, 0, 0);

        auto windowWidth = adjustedWindowRect.right - adjustedWindowRect.left;
        auto windowHeight = adjustedWindowRect.bottom - adjustedWindowRect.top;

        HWND hWindow = CreateWindow(WindowClassName.c_str(),
                                    windowSettings.title.c_str(),
                                    WS_OVERLAPPEDWINDOW,
                                    x, y, windowWidth, windowHeight,
                                    nullptr, nullptr, hInstance, nullptr);

        if (!hWindow)
        {
            Logger::Message(std::format("WindowBackend: window init fail {}", GetLastError()), Logger::Error);
            return nullptr;
        }

        return new Win32WindowHandle(hWindow);
    }
}