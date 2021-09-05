#pragma once

#include <Engine/Window/WindowBackend.h>
#include <Engine/Window/WindowSettings.h>
#include <Platform/Window/Win32WindowHandle.h>

namespace TE
{
    class Win32WindowBackend : public WindowBackend
    {
    public:
        Win32WindowBackend();
        ~Win32WindowBackend();
        bool Init(WindowSettings *windowSettings);
        bool PollEvents();
        void Show();

    private:
        static LRESULT WindowProcedure(HWND hWnd, unsigned int msg, WPARAM wparam, LPARAM lparam);
        static Win32WindowHandle *MakeWindow(WindowSettings *windowSettings);
    };
}