#include <Engine/Render/Render.h>
#include <Engine/Render/VertexBuffer.h>
#include <Platform/Render/GLVertexBuffer.h>
#include <Engine/Logger.h>

namespace TE
{
    std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void *vertices, uint32_t size)
    {
        auto renderApiType = Render::GetApiType();
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
            Logger::Message("VertexBuffer: unknown render api", Logger::Error);
        }

        return vertexBuffer;
    }
}