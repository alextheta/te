#include <Windows.h>

#include <Platform/Window/Win32WindowHandle.h>

namespace TE
{
    Win32WindowHandle::Win32WindowHandle(HWND hWnd)
    {
        _hWindow = hWnd;
    }

    void * const Win32WindowHandle::GetRawHandle() const
    {
        return _hWindow;
    }
}