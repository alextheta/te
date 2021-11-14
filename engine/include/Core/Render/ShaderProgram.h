#pragma once

#include <memory>

#include <Core/Common.h>
#include <Core/Render/Shader.h>

namespace TE
{
    class TE_API ShaderProgram
    {
    public:
        std::string name;

        ShaderProgram(const std::string &name, const std::initializer_list<std::shared_ptr<Shader>> &shaders);
        virtual ~ShaderProgram() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual bool IsValid() = 0;

        static std::shared_ptr<ShaderProgram> Create(const std::string &name, const std::initializer_list<std::shared_ptr<Shader>> &shaders);
    };
}