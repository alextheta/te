#pragma once

#include <Windows.h>
#include <Engine/Window/WindowHandle.h>

namespace TE
{
    class Win32WindowHandle final: public WindowHandle
    {
    public:
        Win32WindowHandle(HWND hWnd);
        virtual void *GetRawHandle() override;

    private:
        HWND _hWindow;
    };
}