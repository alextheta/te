#include <Engine/Render/Render.h>
#include <Engine/Logger.h>

namespace TE
{
    Render::Render(RenderBackend *backend)
    {
        Logger::Instance().Message("Render: instantiate");

        if (!backend)
        {
            Logger::Instance().Message("Render: backend is null", Logger::Error);
            return;
        }

        _renderBackend = std::unique_ptr<RenderBackend>(backend);
    }

    Render::~Render()
    {
        Logger::Instance().Message("Render: destroy");
    }

    bool Render::Init(Window *window)
    {
        Logger::Instance().Message("Render: init");

        if (!window)
        {
            Logger::Instance().Message("Render: window is null", Logger::Error);
            return false;
        }

        return  _renderBackend->Init(window->GetBackend());
    }

    void Render::Draw()
    {
        _renderBackend->Clear();
        _renderBackend->ProcessSwapChain();
    }
}