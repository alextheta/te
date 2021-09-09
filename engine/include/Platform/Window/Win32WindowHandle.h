#pragma once

#include <Windows.h>
#include <Engine/Window/WindowHandle.h>

namespace TE
{
    class Win32WindowHandle : public WindowHandle
    {
    public:
        Win32WindowHandle(HWND hWnd);
        void *GetHandle();

    private:
        HWND _hWindow;
    };
}