#pragma once

#include <memory>

#include <Engine/Window/WindowSettings.h>
#include <Engine/Window/WindowHandle.h>
#include <Engine/Event/Event.h>

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

        inline static Event<void()> WindowCloseEvent;

    protected:
        std::unique_ptr<WindowHandle> _windowHandle;
    };
}