#include <Engine/Logger.h>
#include <Engine/Window/Window.h>

namespace TE
{
    Window::Window(WindowBackend *backend)
    {
        Logger::Instance().Message("Window: instantiate");

        if (!backend)
        {
            Logger::Instance().Message("Window: backend is null", Logger::Error);
            return;
        }

        _windowBackend = std::unique_ptr<WindowBackend>(backend);
    }

    Window::~Window()
    {
        Logger::Instance().Message("Window: destroy");
    }

    bool Window::Init(WindowSettings *settings)
    {
        Logger::Instance().Message("Window: init");

        if (!settings)
        {
            Logger::Instance().Message("Window: settings is null", Logger::Error);
            return false;
        }

        return _windowBackend->Init(settings);
    }

    bool Window::PollEvents()
    {
        return _windowBackend->PollEvents();
    }

    void Window::Show()
    {
        return _windowBackend->Show();
    }

    WindowBackend *Window::GetBackend()
    {
        return _windowBackend.get();
    }
}
