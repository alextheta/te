#pragma once

#include <memory>
#include <glm/glm.hpp>

#include <Core/Common.h>
#include <Core/Render/Shader.h>

namespace TE
{
    class TE_API ShaderProgram
    {
    public:
        std::string name;

        ShaderProgram(const std::string &name, const std::initializer_list<std::shared_ptr<Shader>> &shaders);
        virtual ~ShaderProgram() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual bool IsValid() const = 0;

        virtual void SetProperty(const std::string &propertyName, bool &data) = 0;
        virtual void SetProperty(const std::string &propertyName, int32_t &data) = 0;
        virtual void SetProperty(const std::string &propertyName, float &data) = 0;
        virtual void SetProperty(const std::string &propertyName, glm::vec2 &data) = 0;
        virtual void SetProperty(const std::string &propertyName, glm::vec3 &data) = 0;
        virtual void SetProperty(const std::string &propertyName, glm::vec4 &data) = 0;
        virtual void SetProperty(const std::string &propertyName, glm::mat3 &data) = 0;
        virtual void SetProperty(const std::string &propertyName, glm::mat4 &data) = 0;
        virtual bool ContainsProperty(const std::string &propertyName) const = 0;

        static std::shared_ptr<ShaderProgram> Create(const std::string &name, const std::initializer_list<std::shared_ptr<Shader>> &shaders);
    };
}