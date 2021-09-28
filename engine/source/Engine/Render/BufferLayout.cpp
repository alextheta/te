#include <Engine/Render/BufferLayout.h>

namespace TE
{
    BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements) : _elements(elements), _stride(0)
    {
        size_t offset = 0;
        for (auto &element : _elements)
        {
            element.offset = offset;
            offset += element.size;
            _stride += element.size;
        }
    }

    uint32_t BufferLayout::GetStride() const
    {
        return _stride;
    }

    const std::vector<BufferElement> &BufferLayout::GetElements() const
    {
        return _elements;
    }
}
