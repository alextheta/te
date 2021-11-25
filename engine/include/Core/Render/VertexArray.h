#pragma once

#include <Core/Render/VertexBuffer.h>
#include <Core/Render/IndexBuffer.h>

namespace TE
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) = 0;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) = 0;

        virtual const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const = 0;
        virtual const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const = 0;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual bool IsValid() = 0;

        static std::shared_ptr<VertexArray> Create();
    };
}