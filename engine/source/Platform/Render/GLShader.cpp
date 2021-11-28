#include <vector>
#include <format>

#include <Core/Logger.h>
#include <Platform/Render/GLShader.h>

namespace TE
{
    GLShader::GLShader(const std::string &name, const std::string &source, ShaderType type) : Shader(name, source, type)
    {
        GLint compileResult = GL_FALSE;
        const char *sourcePtr = source.c_str();
        GLuint glShaderType;

        switch (_shaderType)
        {
            case Vertex:
                glShaderType = GL_VERTEX_SHADER;
                break;
            case Fragment:
                glShaderType = GL_FRAGMENT_SHADER;
                break;
        }

        _id = glCreateShader(glShaderType);
        glShaderSource(_id, 1, &sourcePtr, nullptr);
        glCompileShader(_id);

        glGetShaderiv(_id, GL_COMPILE_STATUS, &compileResult);
        if (compileResult != GL_TRUE)
        {
            GLint compileLogLength;
            glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &compileLogLength);
            auto compileError = std::make_unique<GLchar[]>(compileLogLength);
            glGetShaderInfoLog(_id, compileLogLength, nullptr, &compileError[0]);

            Logger::Message(std::format("Shader \"{}\" GLSL error:\n{}", name, &compileError[0]), Logger::Warning);

            glDeleteShader(_id);
            _id = NULL;
        }
    }

    GLShader::~GLShader()
    {
        _id = NULL;
    }

    GLuint GLShader::GetId() const
    {
        return _id;
    }

    bool GLShader::IsValid() const
    {
        return _id != NULL;
    }
}