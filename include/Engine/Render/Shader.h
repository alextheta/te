#pragma once

#include <string>

namespace TE
{
    enum ShaderType
    {
        Vertex,
        Fragment
    };

    class Shader
    {
    public:
        std::string name;

        Shader(const std::string &name, const std::string &source, ShaderType type);
        virtual ~Shader() = default;

        virtual bool IsValid() = 0;

    protected:
        ShaderType _shaderType;
    };
}