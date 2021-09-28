#pragma once

#include <memory>

#include <Engine/Window/WindowBackend.h>
#include <Engine/Render/ShaderDataTypeWrapper.h>
#include <Engine/Common.h>

namespace TE
{
    enum RenderApiType
    {
        Unknown,
        OpenGL
    };

    class TE_API RenderBackend
    {
    public:
        virtual ~RenderBackend() = default;
        virtual bool Init(const WindowBackend *const windowBackend) = 0;

        virtual void Clear() = 0;
        virtual void ProcessSwapChain() = 0;

        RenderApiType GetApiType();
        ShaderDataTypeWrapper *const GetShaderDataTypeWrapper();

    protected:
        RenderApiType _renderApiType;
        std::shared_ptr<ShaderDataTypeWrapper> _shaderDataTypeWrapper;
    };
}