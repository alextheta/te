#pragma once

#include <Core/Common.h>
#include <Core/Window/WindowBackend.h>
#include <Core/Event/Event.h>

namespace TE
{
    class TE_API Window
    {
    public:
        Window(WindowBackend *backend);
        ~Window();
        bool Init(WindowSettings &settings);
        void PollEvents() const;
        void Show() const;

        const WindowBackend * const GetBackend() const;

        Event<void()> WindowCloseEvent;
        Event<void(uint32_t, uint32_t)> WindowResizeEvent;

    private:
        std::unique_ptr<WindowBackend> _windowBackend;

        void OnWindowClose();
        void OnWindowResize(uint32_t width, uint32_t height);
    };
}