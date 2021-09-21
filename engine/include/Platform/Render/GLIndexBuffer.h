#pragma once

#include <GL/gl3w.h>

#include <Engine/Render/IndexBuffer.h>
#include <cstdint>

namespace TE
{
    class GLIndexBuffer : public IndexBuffer
    {
    public:
        GLIndexBuffer(int32_t *indices, uint32_t count);
        ~GLIndexBuffer();

        uint32_t GetCount();
        void Bind();
        void Unbind();
        bool IsValid();

    private:
        GLuint _id;
        uint32_t _count;
    };
}