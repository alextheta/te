#pragma once

#include <string>

#include <Core/Common.h>
#include <Core/Render/ShaderDataTypeWrapper.h>

namespace TE
{
    class TE_API BufferElement final
    {
    public:
        BufferElement(ShaderDataType type, const std::string &name, bool normalized = false);
        ~BufferElement() = default;

        uint32_t GetComponentCount() const;

        std::string name;
        ShaderDataType type;
        uint32_t size;
        uint32_t offset;
        bool normalized;
    };
}