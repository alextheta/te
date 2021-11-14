#include <vector>
#include <format>

#include <Core/Logger.h>
#include <Platform/Render/GLShaderProgram.h>
#include <Platform/Render/GLShader.h>

namespace TE
{
    GLShaderProgram::GLShaderProgram(const std::string &name, const std::initializer_list<std::shared_ptr<Shader>> &shaders) : ShaderProgram(name, shaders)
    {
        _id = glCreateProgram();

        for(auto shader : shaders)
        {
            if (!shader->IsValid())
            {
                Logger::Message(std::format("ShaderProgram \"{}\": shader \"{}\" is invalid", name, shader->name), Logger::Warning);
                glDeleteProgram(_id);
                _id = NULL;
                return;
            }

            auto glShader = static_pointer_cast<GLShader>(shader);
            glAttachShader(_id, glShader->GetId());
        }

        glLinkProgram(_id);

        int32_t linkStatus;
        glGetProgramiv(_id, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE)
        {
            GLint compileLogLength;
            glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &compileLogLength);
            auto compileError = std::make_unique<GLchar[]>(compileLogLength);
            glGetProgramInfoLog(_id, compileLogLength, nullptr, &compileError[0]);

            Logger::Message(std::format("ShaderProgram \"{}\": link fail: {} ", name, &compileError[0]), Logger::Warning);

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

    bool GLShaderProgram::IsValid()
    {
        return _id != NULL;
    }
}