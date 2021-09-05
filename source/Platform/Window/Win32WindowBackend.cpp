#include <Windows.h>

#include <Engine/Logger.h>
#include <Platform/Window/Win32WindowBackend.h>
#include <format>

namespace TE
{
    const std::wstring WindowClassName(L"te_window_class");

    Win32WindowBackend::Win32WindowBackend()
    {
        Logger::Instance().Message("WindowBackend: Win32WindowBackend");
    }

    Win32WindowBackend::~Win32WindowBackend()
    {
        Logger::Instance().Message("Win32WindowBackend: destroy");

        HWND hWindow = static_cast<HWND>(GetWindowHandle()->GetHandle());
        HMODULE hInstance = GetModuleHandle(nullptr);

        DestroyWindow(hWindow);
        UnregisterClass(WindowClassName.c_str(), hInstance);
    }

    bool Win32WindowBackend::Init(WindowSettings *windowSettings)
    {
        Logger::Instance().Message("WindowBackend: init");

        if (!windowSettings)
        {
            Logger::Instance().Message("WindowBackend: window settings is null", Logger::Error);
            return false;
        }

        _windowHandle = std::unique_ptr<WindowHandle>(MakeWindow(windowSettings));
        if (!_windowHandle)
        {
            Logger::Instance().Message("WindowBackend: window init fail", Logger::Error);
            return false;
        }

        return true;
    }

    bool Win32WindowBackend::PollEvents()
    {
        MSG msg;
        if (GetMessage(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            return true;
        }

        Logger::Instance().Message("WindowBackend: window is closed");
        return false;
    }

    void Win32WindowBackend::Show()
    {
        ShowWindow(static_cast<HWND>(_windowHandle->GetHandle()), SW_SHOW);
    }

    LRESULT Win32WindowBackend::WindowProcedure(HWND hWnd, unsigned int msg, WPARAM wparam, LPARAM lparam)
    {
        switch (msg)
        {
            case WM_CREATE:
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            case WM_CLOSE:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, msg, wparam, lparam);
        }
        return 0;
    }

    Win32WindowHandle *Win32WindowBackend::MakeWindow(WindowSettings *windowSettings)
    {
        HMODULE hInstance = GetModuleHandle(nullptr);
        if (!hInstance)
        {
            Logger::Instance().Message(std::format("WindowBackend: instance handle is null {}", GetLastError()), Logger::Error);
            return nullptr;
        }

        WNDCLASSEX windowClass;
        memset(&windowClass, 0, sizeof(WNDCLASSEX));
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.style = CS_DBLCLKS;
        windowClass.lpfnWndProc = WindowProcedure;
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
            Logger::Instance().Message(std::format("WindowBackend: class registration fail {}", GetLastError()), Logger::Error);
            return nullptr;
        }

        RECT desktopRect;
        if (!GetWindowRect(GetDesktopWindow(), &desktopRect))
        {
            Logger::Instance().Message(std::format("WindowBackend: desktop rect obtain fail {}", GetLastError()), Logger::Error);
            return nullptr;
        }

        auto x = (desktopRect.right / 2) - (windowSettings->width / 2);
        auto y = (desktopRect.bottom / 2) - (windowSettings->height / 2);

        HWND hWindow = CreateWindow(
                WindowClassName.c_str(),
                windowSettings->title.c_str(),
                WS_OVERLAPPEDWINDOW,
                x, y, windowSettings->width, windowSettings->height,
                nullptr, nullptr, hInstance, nullptr);

        if (!hWindow)
        {
            Logger::Instance().Message(std::format("WindowBackend: window init fail {}", GetLastError()), Logger::Error);
            return nullptr;
        }

        return new Win32WindowHandle(hWindow);
    }
}