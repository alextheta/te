#pragma once

#include <memory>

#include <Engine/Render/RenderBackend.h>
#include <Engine/Window/Window.h>
#include <Engine/Render/ShaderDataTypeWrapper.h>
#include <Engine/Common.h>

namespace TE
{
    class TE_API Render
    {
    public:
        Render(RenderBackend *const backend);
        ~Render();
        bool Init(const Window *const window);

        void Clear() const;
        void ProcessSwapChain() const;

        static RenderApiType GetApiType();
        static uint32_t GetShaderDataTypeSize(ShaderDataType type);
        static uint32_t GetVendorShaderDataType(ShaderDataType type);

    private:
        std::unique_ptr<RenderBackend> _renderBackend;

        inline static RenderApiType _renderApiType = Unknown;
        inline static ShaderDataTypeWrapper *_shaderDataTypeWrapper = nullptr;
    };
}
