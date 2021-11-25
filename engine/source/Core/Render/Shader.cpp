#include <format>

#include <Core/Logger.h>
#include <Core/Core.h>
#include <Core/Render/Render.h>
#include <Core/Render/Shader.h>

#include <Platform/Render/GLShader.h>

namespace TE
{
    Shader::Shader(const std::string &name, const std::string &source, ShaderType type)
    {
        this->name = name;
        _shaderType = type;
    }

    std::shared_ptr<Shader> Shader::Create(const std::string &name, const std::string &source, ShaderType type)
    {
        auto renderApiType = RenderApi::GetApiType();

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