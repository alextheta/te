#pragma once

#include <GL/gl3w.h>

#include <Engine/Render/ShaderProgram.h>

namespace TE
{
    class GLShaderProgram : public ShaderProgram
    {
    public:
        GLShaderProgram(const std::string &name, const std::initializer_list<std::shared_ptr<Shader>> &shaders);
        ~GLShaderProgram();

        void Bind();
        void Unbind();
        bool IsValid();

    private:
        GLuint _id;
    };
}