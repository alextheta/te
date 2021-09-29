#include <Engine/Logger.h>
#include <Engine/Window/Window.h>

namespace TE
{
    Window::Window(WindowBackend *backend)
    {
        Logger::Message("Window: instantiate");

        if (!backend)
        {
            Logger::Message("Window: backend is null", Logger::Error);
            return;
        }

        backend->WindowCloseEvent.AddListener(&Window::OnWindowClose, this);

        _windowBackend = std::unique_ptr<WindowBackend>(backend);
    }

    Window::~Window()
    {
        Logger::Message("Window: destroy");
    }

    bool Window::Init(WindowSettings &settings)
    {
        Logger::Message("Window: init");

        return _windowBackend->Init(settings);
    }

    void Window::PollEvents() const
    {
        _windowBackend->PollEvents();
    }

    void Window::Show() const
    {
        return _windowBackend->Show();
    }

    const WindowBackend * const Window::GetBackend() const
    {
        return _windowBackend.get();
    }

    void Window::OnWindowClose()
    {
        WindowCloseEvent();
    }
}
