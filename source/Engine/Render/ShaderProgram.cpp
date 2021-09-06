#include <Engine/Render/ShaderProgram.h>

namespace TE
{
    ShaderProgram::ShaderProgram(std::string name, std::initializer_list<Shader*> shaders)
    {
        this->name = name;
    }
}