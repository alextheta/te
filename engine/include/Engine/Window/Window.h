#pragma once

#include <Engine/Window/WindowBackend.h>
#include <Engine/Event/Event.h>
#include <Engine/Common.h>

namespace TE
{
    class TE_API Window
    {
    public:
        Window(WindowBackend *backend);
        ~Window();
        bool Init(WindowSettings &settings);
        void PollEvents();
        void Show();

        const WindowBackend * const GetBackend() const;

        Event<void()> WindowCloseEvent;

    private:
        std::unique_ptr<WindowBackend> _windowBackend;

        void OnWindowClose();
    };
}