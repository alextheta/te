#pragma once

#include <GL/gl3w.h>

#include <Core/Render/ShaderProgram.h>

namespace TE
{
    class GLShaderProgram final: public ShaderProgram
    {
    public:
        GLShaderProgram(const std::string &name, const std::initializer_list<std::shared_ptr<Shader>> &shaders);
        virtual ~GLShaderProgram() override;

        virtual void Bind() override;
        virtual void Unbind() override;
        virtual bool IsValid() override;

    private:
        GLuint _id;
    };
}