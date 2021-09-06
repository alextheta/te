#pragma once

#include <memory>

#include <Engine/Render/Shader.h>

namespace TE
{
    class ShaderProgram
    {
    public:
        std::string name;

        ShaderProgram(std::string name, std::initializer_list<Shader*> shaders);
        virtual ~ShaderProgram() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
    };
}