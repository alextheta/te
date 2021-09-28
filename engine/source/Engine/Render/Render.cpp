#include <Engine/Render/Render.h>
#include <Engine/Logger.h>
#include <Engine/Core.h>

#include <format>

namespace TE
{
    Render::Render(RenderBackend *const backend)
    {
        Logger::Message("Render: instantiate");

        if (!backend)
        {
            Logger::Message("Render: backend is null", Logger::Error);
            return;
        }

        _renderBackend = std::unique_ptr<RenderBackend>(backend);
        _renderApiType = _renderBackend->GetApiType();
        _shaderDataTypeWrapper = _renderBackend->GetShaderDataTypeWrapper();
    }

    Render::~Render()
    {
        Logger::Message("Render: destroy");
    }

    bool Render::Init(const Window *const window)
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

    RenderApiType Render::GetApiType()
    {
        return _renderApiType;
    }

    uint32_t Render::GetShaderDataTypeSize(ShaderDataType type)
    {
        return _shaderDataTypeWrapper->GetShaderDataTypeSize(type);
    }

    uint32_t Render::GetVendorShaderDataType(ShaderDataType type)
    {
        return _shaderDataTypeWrapper->GetVendorShaderDataType(type);
    }
}