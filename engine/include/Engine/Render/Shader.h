#pragma once

#include <string>

#include <Engine/Common.h>

namespace TE
{
    enum ShaderType
    {
        Vertex,
        Fragment
    };

    class TE_API Shader
    {
    public:
        std::string name;

        Shader(const std::string &name, const std::string &source, ShaderType type);
        virtual ~Shader() = default;

        virtual bool IsValid() = 0;

        static std::shared_ptr<Shader> Create(const std::string &name, const std::string &source, ShaderType type);

    protected:
        ShaderType _shaderType;
    };
}