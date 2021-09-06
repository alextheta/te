#include <Engine/Render/Shader.h>

namespace TE
{
    Shader::Shader(const std::string &name, const std::string &source, ShaderType type)
    {
        this->name = name;
        _shaderType = type;
    }
}