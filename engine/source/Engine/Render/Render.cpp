#include <Engine/Render/Render.h>
#include <Engine/Logger.h>
#include <Engine/Core.h>

namespace TE
{
    Render::Render(RenderBackend *backend)
    {
        Logger::Message("Render: instantiate");

        if (!backend)
        {
            Logger::Message("Render: backend is null", Logger::Error);
            return;
        }

        _renderBackend = std::unique_ptr<RenderBackend>(backend);
        _renderApiType = _renderBackend->GetApiType();
    }

    Render::~Render()
    {
        Logger::Message("Render: destroy");
    }

    bool Render::Init(Window *window)
    {
        Logger::Message("Render: init");

        if (!window)
        {
            Logger::Message("Render: window is null", Logger::Error);
            return false;
        }

        return  _renderBackend->Init(window->GetBackend());
    }

    void Render::Clear()
    {
        _renderBackend->Clear();
    }

    void Render::Draw()
    {
        _renderBackend->ProcessSwapChain();
    }
}