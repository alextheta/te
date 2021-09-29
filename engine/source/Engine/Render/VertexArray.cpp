#include <Engine/Render/VertexArray.h>
#include <Engine/Render/Render.h>
#include <Platform/Render/GLVertexArray.h>

namespace TE
{
    std::shared_ptr<VertexArray> VertexArray::Create()
    {
        auto renderApiType = Render::GetApiType();

        switch (renderApiType)
        {
            case OpenGL:
            {
                return std::make_shared<GLVertexArray>();
            }
        }

        return nullptr;
    }
}