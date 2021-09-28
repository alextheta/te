#pragma once

#include <Engine/Common.h>

namespace TE
{
    enum ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    class TE_API ShaderDataTypeWrapper
    {
    public:
        virtual ~ShaderDataTypeWrapper() = default;

        virtual uint32_t GetShaderDataTypeSize(ShaderDataType type) = 0;
        virtual uint32_t GetVendorShaderDataType(ShaderDataType type) = 0;
    };
}