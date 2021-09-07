#include <format>

#include <Engine/Render/Render.h>
#include <Engine/Render/ShaderProgram.h>
#include <Engine/Logger.h>

#include <Platform/Render/GLShaderProgram.h>

namespace TE
{
    ShaderProgram::ShaderProgram(const std::string &name, const std::initializer_list<std::shared_ptr<Shader>> &shaders)
    {
        this->name = name;
    }

    std::shared_ptr<ShaderProgram> ShaderProgram::Create(const std::string &name, const std::initializer_list<std::shared_ptr<Shader>> &shaders)
    {
        auto renderApiType = Render::GetApiType();

        switch (renderApiType)
        {
            case OpenGL:
            {
                return std::make_shared<GLShaderProgram>(name, shaders);
            }
        }

        Logger::Instance().Message(std::format("ShaderProgram \"{}\": unknown render api", name), Logger::Error);
        return nullptr;
    }
}