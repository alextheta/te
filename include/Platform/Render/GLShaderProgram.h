#pragma once

#include <GL/gl3w.h>

#include <Engine/Render/ShaderProgram.h>

namespace TE
{
    class GLShaderProgram : public ShaderProgram
    {
    public:
        GLShaderProgram(std::string name, std::initializer_list<Shader*> shaders);
        ~GLShaderProgram();

        void Bind();
        void Unbind();

    private:
        GLuint _id;
    };
}