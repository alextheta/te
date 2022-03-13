#include <format>

#include <Core/Logger.h>
#include <Core/Render/Render.h>
#include <Core/Render/ShaderProgram.h>
#include <Platform/Render/GLShaderProgram.h>

namespace TE
{
    ShaderProgram::ShaderProgram(const std::string &name, const std::initializer_list<std::shared_ptr<Shader>> &shaders)
    {
        this->name = name;
    }

    std::shared_ptr<ShaderProgram> ShaderProgram::Create(const std::string &name, const std::initializer_list<std::shared_ptr<Shader>> &shaders)
    {
        auto renderApiType = RenderApi::GetApiType();

        switch (renderApiType)
        {
            case OpenGL:
            {
                return std::make_shared<GLShaderProgram>(name, shaders);
            }
        }

        Logger::Message(std::format("ShaderProgram \"{}\": unknown render API", name), Logger::Error);
        return nullptr;
    }
}