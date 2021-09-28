#pragma once

#include <Engine/Window/WindowBackend.h>
#include <Engine/Window/WindowSettings.h>
#include <Platform/Window/Win32WindowHandle.h>
#include <Engine/Common.h>

namespace TE
{
    class TE_API Win32WindowBackend final: public WindowBackend
    {
    public:
        Win32WindowBackend();
        virtual ~Win32WindowBackend() override;
        virtual bool Init(WindowSettings &windowSettings) override;
        virtual void PollEvents() override;
        virtual void Show() override;

        static void OverrideWindowProcedure(LRESULT (*WindowProcedurePointer)(HWND hWnd, unsigned int msg, WPARAM wparam, LPARAM lparam));

    private:
        inline static LRESULT (*WindowProcedureOverride)(HWND hWnd, unsigned int msg, WPARAM wparam, LPARAM lparam);
        static LRESULT WindowProcedure(HWND hWnd, unsigned int msg, WPARAM wparam, LPARAM lparam);
        static Win32WindowHandle * const MakeWindow(WindowSettings &windowSettings);
    };
}