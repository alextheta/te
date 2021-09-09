#pragma once

#include <memory>

#include <Engine/Window/WindowSettings.h>
#include <Engine/Window/WindowHandle.h>

namespace TE
{
    class WindowBackend
    {
    public:
        virtual ~WindowBackend() = default;
        virtual bool Init(WindowSettings *windowSettings) = 0;
        virtual bool PollEvents() = 0;
        virtual void Show() = 0;

        WindowHandle *GetWindowHandle();

    protected:
        std::unique_ptr<WindowHandle> _windowHandle;
    };
}