#include <memory>

#include <Engine/Logger.h>
#include <Engine/Core.h>


namespace TE
{
    Core::Core(WindowBackend *windowBackend, RenderBackend *renderBackend)
    {
        Logger::Message("Core: instantiate");

        if (!windowBackend)
        {
            Logger::Message("Core: window backend is null");
            return;
        }

        if (!renderBackend)
        {
            Logger::Message("Core: render backend is null");
            return;
        }

        _window = std::make_shared<Window>(windowBackend);
        _render = std::make_shared<Render>(renderBackend);
    }

    Core::~Core()
    {
        Logger::Message("Core: destroy");
        _render.reset();
    }

    bool Core::Init(WindowSettings &windowSettings)
    {
        Logger::Message("Core: init");

        if (!_window->Init(windowSettings))
        {
            Logger::Message("Core: window init fail", Logger::Error);
            return false;
        }

        if (!_render->Init(_window.get()))
        {
            Logger::Message("Core: render init fail", Logger::Error);
            return false;
        }

        _window->Show();

        return true;
    }

    const std::shared_ptr<Window> Core::GetWindow()
    {
        return _window;
    }

    const std::shared_ptr<Render> Core::GetRender()
    {
        return _render;
    }
}