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
        virtual void Bind() override;
        virtual void Unbind() override;
        virtual bool IsValid() override;

    private:
        GLuint _id;
    };
}