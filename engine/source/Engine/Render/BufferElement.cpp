#include <Engine/Render/BufferElement.h>
#include <Engine/Render/Render.h>

namespace TE
{
    BufferElement::BufferElement(ShaderDataType type, const std::string &name, bool normalized) :
            name(name), type(type), size(Render::GetShaderDataTypeSize(type)), offset(0), normalized(normalized)
    {

    }

    uint32_t BufferElement::GetComponentCount() const
    {
        switch (type)
        {

            case ShaderDataType::Int:
            case ShaderDataType::Bool:
            case ShaderDataType::Float:
                return 1;

            case ShaderDataType::Int2:
            case ShaderDataType::Float2:
                return 2;

            case ShaderDataType::Int3:
            case ShaderDataType::Float3:
            case ShaderDataType::Mat3:
                return 3;

            case ShaderDataType::Int4:
            case ShaderDataType::Float4:
            case ShaderDataType::Mat4:
                return 4;

        }

        return 0;
    }
}
