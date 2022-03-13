#pragma once

#include <memory>

#include <Core/Common.h>
#include <Core/Window/WindowSettings.h>
#include <Core/Window/WindowHandle.h>
#include <Core/Event/Event.h>

namespace TE
{
    class TE_API WindowBackend
    {
    public:
        virtual ~WindowBackend() = default;
        virtual bool Init(WindowSettings &windowSettings) = 0;
        virtual void PollEvents() = 0;
        virtual void Show() = 0;

        const WindowHandle * const GetWindowHandle() const;

        inline static Event<void()> WindowCloseEvent;
        inline static Event<void(uint32_t, uint32_t)> WindowResizeEvent;

    protected:
        std::unique_ptr<WindowHandle> _windowHandle;
    };
}