#include <Core/Logger.h>
#include <Core/Render/Render.h>

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

        _renderBackend = std::shared_ptr<RenderBackend>(backend);
        _shaderDataTypeWrapper = _renderBackend->GetShaderDataTypeWrapper();

        RenderApi::_backend = _renderBackend;
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

    uint32_t Render::GetShaderDataTypeSize(ShaderDataType type)
    {
        return _shaderDataTypeWrapper->GetShaderDataTypeSize(type);
    }

    uint32_t Render::GetVendorShaderDataType(ShaderDataType type)
    {
        return _shaderDataTypeWrapper->GetVendorShaderDataType(type);
    }
}