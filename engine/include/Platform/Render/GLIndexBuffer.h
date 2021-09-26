#pragma once

#include <GL/gl3w.h>

#include <Engine/Render/IndexBuffer.h>
#include <cstdint>

namespace TE
{
    class GLIndexBuffer final : public IndexBuffer
    {
    public:
        GLIndexBuffer(int32_t *indices, uint32_t count);
        virtual ~GLIndexBuffer() override;

        virtual uint32_t GetCount() override;
        virtual void Bind() override;
        virtual void Unbind() override;
        virtual bool IsValid() override;

    private:
        GLuint _id;
        uint32_t _count;
    };
}