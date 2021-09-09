#pragma once

#include <memory>

namespace TE
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void SetData(const void* data, uint32_t size) = 0;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual bool IsValid() = 0;

        static std::shared_ptr<VertexBuffer> Create(const void *vertices, uint32_t size);
    };
}