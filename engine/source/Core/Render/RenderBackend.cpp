#include <Core/Render/RenderBackend.h>

namespace TE
{
    RenderApiType RenderBackend::GetApiType()
    {
        return _renderApiType;
    }

    ShaderDataTypeWrapper *const RenderBackend::GetShaderDataTypeWrapper()
    {
        return _shaderDataTypeWrapper.get();
    }
}