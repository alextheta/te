#include <Core/Logger.h>
#include <Core/Render/Render.h>
#include <Core/Render/IndexBuffer.h>
#include <Platform/Render/GLIndexBuffer.h>

namespace TE
{
    std::shared_ptr<IndexBuffer> IndexBuffer::Create(int32_t *indices, uint32_t count)
    {
        auto renderApiType = RenderApi::GetApiType();

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