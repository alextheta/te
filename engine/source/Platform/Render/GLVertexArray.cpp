#include <Core/Render/Render.h>
#include <Platform/Render/GLVertexArray.h>

namespace TE
{

    GLVertexArray::GLVertexArray()
    {
        glCreateVertexArrays(1, &_id);
    }

    GLVertexArray::~GLVertexArray()
    {
        glDeleteVertexArrays(1, &_id);
    }

    void GLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer)
    {
        glBindVertexArray(_id);
        vertexBuffer->Bind();

        const auto &layout = vertexBuffer->GetLayout();
        for (const auto &element : layout.GetElements())
        {
            switch (element.type)
            {
                case ShaderDataType::Float:
                case ShaderDataType::Float2:
                case ShaderDataType::Float3:
                case ShaderDataType::Float4:
                {
                    glEnableVertexAttribArray(_vertexBufferId);
                    glVertexAttribPointer(_vertexBufferId,
                                          element.GetComponentCount(),
                                          Render::GetVendorShaderDataType(element.type),
                                          element.normalized ? GL_TRUE : GL_FALSE,
                                          layout.GetStride(),
                                          (const void *) element.offset);
                    _vertexBufferId++;
                    break;
                }
                case ShaderDataType::Int:
                case ShaderDataType::Int2:
                case ShaderDataType::Int3:
                case ShaderDataType::Int4:
                case ShaderDataType::Bool:
                {
                    glEnableVertexAttribArray(_vertexBufferId);
                    glVertexAttribIPointer(_vertexBufferId,
                                           element.GetComponentCount(),
                                           Render::GetVendorShaderDataType(element.type),
                                           layout.GetStride(),
                                           (const void *) element.offset);
                    _vertexBufferId++;
                    break;
                }
                case ShaderDataType::Mat3:
                case ShaderDataType::Mat4:
                {
                    uint8_t count = element.GetComponentCount();
                    for (uint8_t i = 0; i < count; i++)
                    {
                        glEnableVertexAttribArray(_vertexBufferId);
                        glVertexAttribPointer(_vertexBufferId,
                                              count,
                                              Render::GetVendorShaderDataType(element.type),
                                              element.normalized ? GL_TRUE : GL_FALSE,
                                              layout.GetStride(),
                                              (const void *) (element.offset + sizeof(float) * count * i));
                        glVertexAttribDivisor(_vertexBufferId, 1);
                        _vertexBufferId++;
                    }
                    break;
                }
            }
        }

        _vertexBuffers.push_back(vertexBuffer);
    }

    void GLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer)
    {
        glBindVertexArray(_id);
        indexBuffer->Bind();
        _indexBuffer = indexBuffer;
    }

    const std::vector<std::shared_ptr<VertexBuffer>> &GLVertexArray::GetVertexBuffers() const
    {
        return _vertexBuffers;
    }

    const std::shared_ptr<IndexBuffer> &GLVertexArray::GetIndexBuffer() const
    {
        return _indexBuffer;
    }

    void GLVertexArray::Bind()
    {
        glBindVertexArray(_id);
    }

    void GLVertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    bool GLVertexArray::IsValid()
    {
        return true;
    }
}