#pragma once

#include <Engine/Window/WindowBackend.h>
#include <Engine/Event/Event.h>

namespace TE
{
    class Window
    {
    public:
        Window(WindowBackend *backend);
        ~Window();
        bool Init(WindowSettings *settings);
        void PollEvents();
        void Show();

        WindowBackend *GetBackend();

        Event<void()> WindowCloseEvent;

    private:
        std::unique_ptr<WindowBackend> _windowBackend;

        void OnWindowClose();
    };
}