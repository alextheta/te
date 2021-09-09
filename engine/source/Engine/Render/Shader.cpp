#include <format>

#include <Engine/Render/Render.h>
#include <Engine/Render/Shader.h>
#include <Engine/Logger.h>

#include <Platform/Render/GLShader.h>
#include <Engine/Core.h>

namespace TE
{
    Shader::Shader(const std::string &name, const std::string &source, ShaderType type)
    {
        this->name = name;
        _shaderType = type;
    }

    std::shared_ptr<Shader> Shader::Create(const std::string &name, const std::string &source, ShaderType type)
    {
        auto renderApiType = Render::GetApiType();

        switch (renderApiType)
        {
            case OpenGL:
            {
                return std::make_shared<GLShader>(name, source, type);
            }
        }

        Logger::Message(std::format("Shader \"{}\": unknown render api", name), Logger::Error);
        return nullptr;
    }
}