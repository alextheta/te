#include <Core/Logger.h>
#include <Core/Render/Render.h>
#include <Platform/Render/GLVertexBuffer.h>

namespace TE
{
    std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void *vertices, uint32_t size)
    {
        auto renderApiType = RenderApi::GetApiType();
        std::shared_ptr<VertexBuffer> vertexBuffer = nullptr;

        switch (renderApiType)
        {
            case OpenGL:
            {
                vertexBuffer = std::make_shared<GLVertexBuffer>();
            }
        }

        if (vertexBuffer)
        {
            vertexBuffer->SetData(vertices, size);
        }
        else
        {
            Logger::Message("VertexBuffer: unknown render API", Logger::Error);
        }

        return vertexBuffer;
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void *vertices, uint32_t size, BufferLayout layout)
    {
        auto result = Create(vertices, size);
        result->SetLayout(layout);
        return result;
    }

    const BufferLayout &VertexBuffer::GetLayout() const
    {
        return *_layout.get();
    }

    void VertexBuffer::SetLayout(const BufferLayout &bufferLayout)
    {
        _layout = std::make_unique<BufferLayout>(bufferLayout);
    }
}