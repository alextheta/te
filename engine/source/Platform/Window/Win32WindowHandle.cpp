#include <Windows.h>

#include <Platform/Window/Win32WindowHandle.h>

namespace TE
{
    Win32WindowHandle::Win32WindowHandle(HWND hWnd)
    {
        _hWindow = hWnd;
    }

    void *Win32WindowHandle::GetHandle()
    {
        return _hWindow;
    }
}