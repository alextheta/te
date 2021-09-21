#include <Engine/Render/Render.h>
#include <Engine/Render/IndexBuffer.h>
#include <Platform/Render/GLIndexBuffer.h>
#include <Engine/Logger.h>

namespace TE
{
    std::shared_ptr<IndexBuffer> IndexBuffer::Create(int32_t *indices, uint32_t count)
    {
        auto renderApiType = Render::GetApiType();

        switch (renderApiType)
        {
            case OpenGL:
            {
                return std::make_shared<GLIndexBuffer>(indices, count);
            }
        }

        Logger::Message("IndexBuffer: unknown render api", Logger::Error);
        return nullptr;
    }
}