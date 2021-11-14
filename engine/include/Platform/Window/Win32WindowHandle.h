#pragma once

#include <Windows.h>
#include <Core/Window/WindowHandle.h>

namespace TE
{
    class Win32WindowHandle final: public WindowHandle
    {
    public:
        Win32WindowHandle(HWND hWnd);
        virtual void * const GetRawHandle() const override;

    private:
        HWND _hWindow;
    };
}