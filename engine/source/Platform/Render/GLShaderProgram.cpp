#include <vector>
#include <format>
#include <glm/gtc/type_ptr.hpp>

#include <Core/Logger.h>
#include <Platform/Render/GLShaderProgram.h>
#include <Platform/Render/GLShader.h>

namespace TE
{
    const int InvalidUniformLocation = -1;

    GLShaderProgram::GLShaderProgram(const std::string &name, const std::initializer_list<std::shared_ptr<Shader>> &shaders) : ShaderProgram(name, shaders)
    {
        _id = glCreateProgram();

        for (auto shader : shaders)
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

    void GLShaderProgram::Bind() const
    {
        glUseProgram(_id);
    }

    void GLShaderProgram::Unbind() const
    {
        glUseProgram(0);
    }

    bool GLShaderProgram::IsValid() const
    {
        return _id != NULL;
    }

    void GLShaderProgram::SetProperty(const std::string &propertyName, bool &data)
    {
        GLint location = GetUniformLocation(propertyName);
        glUniform1i(location, data);
    }

    void GLShaderProgram::SetProperty(const std::string &propertyName, int32_t &data)
    {
        GLint location = GetUniformLocation(propertyName);
        glUniform1i(location, data);
    }

    void GLShaderProgram::SetProperty(const std::string &propertyName, float &data)
    {
        GLint location = GetUniformLocation(propertyName);
        glUniform1f(location, data);
    }

    void GLShaderProgram::SetProperty(const std::string &propertyName, glm::vec2 &data)
    {
        GLint location = GetUniformLocation(propertyName);
        glUniform2f(location, data.x, data.y);
    }

    void GLShaderProgram::SetProperty(const std::string &propertyName, glm::vec3 &data)
    {
        GLint location = GetUniformLocation(propertyName);
        glUniform3f(location, data.x, data.y, data.z);
    }

    void GLShaderProgram::SetProperty(const std::string &propertyName, glm::vec4 &data)
    {
        GLint location = GetUniformLocation(propertyName);
        glUniform4f(location, data.x, data.y, data.z, data.w);
    }

    void GLShaderProgram::SetProperty(const std::string &propertyName, glm::mat3 &data)
    {
        GLint location = GetUniformLocation(propertyName);
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(data));
    }

    void GLShaderProgram::SetProperty(const std::string &propertyName, glm::mat4 &data)
    {
        GLint location = GetUniformLocation(propertyName);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data));
    }

    GLint GLShaderProgram::GetUniformLocation(const std::string &name)
    {
        auto uniform = _uniformCache.find(name);
        if (uniform != _uniformCache.end())
        {
            return uniform->second;
        }

        GLint location = glGetUniformLocation(_id, name.c_str());
        if (location != InvalidUniformLocation)
        {
            _uniformCache[name] = location;
        }

        return location;
    }

    bool GLShaderProgram::ContainsProperty(const std::string &propertyName) const
    {
        auto uniform = _uniformCache.find(propertyName);
        if (uniform != _uniformCache.end())
        {
            return true;
        }

        return glGetUniformLocation(_id, propertyName.c_str()) != InvalidUniformLocation;
    }
}