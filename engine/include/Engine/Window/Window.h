#pragma once

#include <memory>

#include <Engine/Window/WindowBackend.h>

namespace TE
{
    class Window
    {
    public:
        Window(WindowBackend *backend);
        ~Window();
        bool Init(WindowSettings *settings);
        bool PollEvents();
        void Show();

        WindowBackend *GetBackend();

    private:
        std::unique_ptr<WindowBackend> _windowBackend;
    };
}