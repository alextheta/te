#pragma once

#include <GL/gl3w.h>

#include <Core/Render/Shader.h>

namespace TE
{
    class GLShader final: public Shader
    {
    public:
        GLShader(const std::string &name, const std::string &source, ShaderType type);
        virtual ~GLShader() override;

        virtual bool IsValid() override;
        GLuint GetId();

    private:
        GLuint _id;
    };
}