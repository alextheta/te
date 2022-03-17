#include <Core/Render/Render.h>
#include <Platform/Render/GLFrameBuffer.h>

namespace TE
{
    FrameBuffer::FrameBuffer(const Settings &spec) : _settings(spec) {}

    std::shared_ptr<FrameBuffer> FrameBuffer::Create(const Settings &spec)
    {
        auto renderApiType = RenderApi::GetApiType();

        switch (renderApiType)
        {
            case OpenGL:
            {
                return std::make_shared<GLFrameBuffer>(spec);
            }
        }

        return nullptr;
    }
}