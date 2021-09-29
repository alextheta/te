#include <Platform/Render/GLVertexBuffer.h>

namespace TE
{
    GLVertexBuffer::GLVertexBuffer()
    {
        glCreateBuffers(1, &_id);
    }

    GLVertexBuffer::~GLVertexBuffer()
    {
        glDeleteBuffers(1, &_id);
    }

    void GLVertexBuffer::SetData(const void *data, uint32_t size)
    {
        Bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    void GLVertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, _id);
    }

    void GLVertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    bool GLVertexBuffer::IsValid()
    {
        return _id != NULL;
    }
}