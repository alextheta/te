#include <format>

#include <Platform/Render/GLShaderProgram.h>
#include <Platform/Render/GLShader.h>
#include <Engine/Logger.h>

namespace TE
{
    GLShaderProgram::GLShaderProgram(std::string name, std::initializer_list<Shader*> shaders) : ShaderProgram(name, shaders)
    {
        _id = glCreateProgram();

        for(auto shader : shaders)
        {
            if (!shader->IsValid())
            {
                Logger::Instance().Message(std::format("ShaderProgram \"{}\": shader \"{}\" is invalid", name, shader->name), Logger::Warning);
                glDeleteProgram(_id);
                _id = NULL;
                return;
            }

            GLShader *glShader = static_cast<GLShader*>(shader);
            glAttachShader(_id, glShader->GetId());
        }

        glLinkProgram(_id);

        int32_t linkStatus;
        glGetProgramiv(_id, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE)
        {
            Logger::Instance().Message(std::format("ShaderProgram \"{}\": failed to link shaders", name), Logger::Warning);
            glDeleteProgram(_id);
            _id = NULL;
        }
    }

    GLShaderProgram::~GLShaderProgram()
    {
        glDeleteProgram(_id);
        _id = NULL;
    }

    void GLShaderProgram::Bind()
    {
        glUseProgram(_id);
    }

    void GLShaderProgram::Unbind()
    {
        glUseProgram(0);
    }
}