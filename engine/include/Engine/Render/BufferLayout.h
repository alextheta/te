#pragma once

#include <vector>

#include <Engine/Render/BufferElement.h>
#include <Engine/Common.h>

namespace TE
{
    class TE_API BufferLayout
    {
    public:
        BufferLayout(std::initializer_list<BufferElement> elements);
        virtual ~BufferLayout() = default;

        uint32_t GetStride() const;
        const std::vector<BufferElement> &GetElements() const;

    private:
        std::vector<BufferElement> _elements;
        uint32_t _stride;
    };
}