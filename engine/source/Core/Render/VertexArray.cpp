#include <Core/Render/VertexArray.h>
#include <Core/Render/Render.h>
#include <Platform/Render/GLVertexArray.h>

namespace TE
{
    std::shared_ptr<VertexArray> VertexArray::Create()
    {
        auto renderApiType = RenderApi::GetApiType();

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