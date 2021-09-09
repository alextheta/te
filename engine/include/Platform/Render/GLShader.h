#pragma once

#include <GL/gl3w.h>

#include <Engine/Render/Shader.h>

namespace TE
{
    class GLShader : public Shader
    {
    public:
        GLShader(const std::string &name, const std::string &source, ShaderType type);
        ~GLShader();

        bool IsValid();
        GLuint GetId();

    private:
        GLuint _id;
    };
}