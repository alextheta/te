#include <vector>
#include <format>

#include <Platform/Render/GLShader.h>
#include <Engine/Logger.h>

namespace TE
{
    GLShader::GLShader(const std::string &name, const std::string &source, ShaderType type) : Shader(name, source, type)
    {
        GLint compileResult = GL_FALSE;
        const char *sourcePtr = source.c_str();
        int32_t compileLogLength;
        GLuint glShaderType;

        switch (_shaderType)
        {
            case Vertex:
                glShaderType = GL_VERTEX_SHADER;
                break;
            case Fragment:
                glShaderType = GL_VERTEX_SHADER;
                break;
        }

        _id = glCreateShader(glShaderType);
        glShaderSource(_id, 1, &sourcePtr, nullptr);
        glCompileShader(_id);

        glGetShaderiv(_id, GL_COMPILE_STATUS, &compileResult);
        if (compileResult != GL_TRUE)
        {
            glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &compileLogLength);
            GLchar *compileError = new GLchar [compileLogLength];
            glGetShaderInfoLog(_id, compileLogLength, nullptr, &compileError[0]);
            Logger::Instance().Message(std::format("GLSL:\n{}", compileError), Logger::Warning);
            glDeleteShader(_id);
            _id = NULL;
        }
    }

    GLShader::~GLShader()
    {
        _id = NULL;
    }

    GLuint GLShader::GetId()
    {
        return _id;
    }

    bool GLShader::IsValid()
    {
        return _id != NULL;
    }
}