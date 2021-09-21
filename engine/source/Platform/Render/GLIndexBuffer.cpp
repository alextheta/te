#include <Platform/Render/GLIndexBuffer.h>

namespace TE
{
    GLIndexBuffer::GLIndexBuffer(int32_t *indices, uint32_t count) : _count(count)
    {
        glCreateBuffers(1, &_id);
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    GLIndexBuffer::~GLIndexBuffer()
    {
        glDeleteBuffers(1, &_id);
    }

    uint32_t GLIndexBuffer::GetCount()
    {
        return _count;
    }

    void GLIndexBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    }

    void GLIndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    bool GLIndexBuffer::IsValid()
    {
        return _id != NULL;
    }
}