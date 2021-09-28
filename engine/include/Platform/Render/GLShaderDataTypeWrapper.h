#pragma once

#include <cstdint>

#include <Engine/Render/ShaderDataTypeWrapper.h>

namespace TE
{
    class GLShaderDataTypeWrapper final: public ShaderDataTypeWrapper
    {
    public:
        virtual ~GLShaderDataTypeWrapper() override;

        virtual uint32_t GetShaderDataTypeSize(ShaderDataType type) override;
        virtual uint32_t GetVendorShaderDataType(ShaderDataType type) override;
    };
}