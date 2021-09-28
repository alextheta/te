#pragma once

#include <GL/gl3w.h>

#include <Engine/Render/VertexBuffer.h>

namespace TE
{
    class GLVertexBuffer final : public VertexBuffer
    {
    public:
        GLVertexBuffer();
        virtual ~GLVertexBuffer();

        virtual void SetData(const void *data, uint32_t size) override;
        virtual const BufferLayout& GetLayout() const override;
        virtual void SetLayout(const BufferLayout& layout) override;
        virtual void Bind() override;
        virtual void Unbind() override;
        virtual bool IsValid() override;

    private:
        GLuint _id;
        std::unique_ptr<BufferLayout> _layout;
    };
}