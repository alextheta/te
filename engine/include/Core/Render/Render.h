#pragma once

#include <memory>

#include <Core/Common.h>
#include <Core/Render/RenderApi.h>
#include <Core/Render/RenderBackend.h>
#include <Core/Window/Window.h>
#include <Core/Render/ShaderDataTypeWrapper.h>

namespace TE
{
    class TE_API Render
    {
    public:
        Render(RenderBackend *const backend);
        ~Render();
        bool Init(const Window *const window);

        static uint32_t GetShaderDataTypeSize(ShaderDataType type);
        static uint32_t GetVendorShaderDataType(ShaderDataType type);

    private:
        std::shared_ptr<RenderBackend> _renderBackend;

        inline static ShaderDataTypeWrapper *_shaderDataTypeWrapper = nullptr;
    };
}
