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

        _window = std::make_unique<Window>(windowBackend);
        _render = std::make_unique<Render>(renderBackend);
    }

    Core::~Core()
    {
        Logger::Message("Core: destroy");
        _render.reset();
    }

    bool Core::Init(WindowSettings *windowSettings)
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

    void Core::Run()
    {
        if (!_window || !_render)
        {
            Logger::Message("Core: unable to run", Logger::Error);
            return;
        }

        while (_window->PollEvents())
        {
            _render->Clear();
            _render->Draw();
        }
    }
}