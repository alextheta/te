#pragma once

#include <memory>

#include <Core/Render/BufferLayout.h>

namespace TE
{
    class TE_API VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void SetData(const void *data, uint32_t size) = 0;
        virtual void SetLayout(const BufferLayout &bufferLayout) final;
        virtual const BufferLayout &GetLayout() const final;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual bool IsValid() = 0;

        static std::shared_ptr<VertexBuffer> Create(const void *vertices, uint32_t size);
        static std::shared_ptr<VertexBuffer> Create(const void *vertices, uint32_t size, BufferLayout layout);

    protected:
        std::unique_ptr<BufferLayout> _layout;
    };
}