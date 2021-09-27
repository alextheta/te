#include <Engine/Render/Render.h>
#include <Engine/Logger.h>
#include <Engine/Core.h>

#include <format>

namespace TE
{
    Render::Render(RenderBackend * const backend)
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

    RenderApiType Render::GetApiType()
    {
        return _renderApiType;
    }

    Render::~Render()
    {
        Logger::Message("Render: destroy");
    }

    bool Render::Init(const Window * const window)
    {
        Logger::Message("Render: init");

        if (!window)
        {
            Logger::Message("Render: window is null", Logger::Error);
            return false;
        }

        return _renderBackend->Init(window->GetBackend());
    }

    void Render::Clear()
    {
        _renderBackend->Clear();
    }

    void Render::ProcessSwapChain()
    {
        _renderBackend->ProcessSwapChain();
    }
}