#pragma once

#include <GL/gl3w.h>

#include <Core/Render/VertexArray.h>

namespace TE
{
    class GLVertexArray final : public VertexArray
    {
    public:
        GLVertexArray();
        virtual ~GLVertexArray() override;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const;
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const;

        virtual void Bind() override;
        virtual void Unbind() override;
        virtual bool IsValid() override;

    private:
        GLuint _id;
        GLuint _vertexBufferId = 0;
        std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffers;
        std::shared_ptr<IndexBuffer> _indexBuffer;
    };
}