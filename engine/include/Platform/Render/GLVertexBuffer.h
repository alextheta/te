#pragma once

#include <GL/gl3w.h>

#include <Engine/Render/VertexBuffer.h>

namespace TE
{
    class GLVertexBuffer : public VertexBuffer
    {
    public:
        GLVertexBuffer();
        ~GLVertexBuffer();

        void SetData(const void* data, uint32_t size);
        void Bind();
        void Unbind();
        bool IsValid();

    private:
        GLuint _id;
    };
}