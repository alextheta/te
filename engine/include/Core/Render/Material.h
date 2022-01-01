#pragma once

#include <unordered_map>

#include <Core/Render/ShaderProgram.h>
#include <Core/Render/MaterialProperty.h>

namespace TE
{
    class Material
    {
    public:
        Material(std::shared_ptr<ShaderProgram> &shader);

        void Bind();
        bool IsValid();

        void SetProperty(const std::string &propertyName, bool data);
        void SetProperty(const std::string &propertyName, int32_t data);
        void SetProperty(const std::string &propertyName, float data);
        void SetProperty(const std::string &propertyName, glm::vec2 data);
        void SetProperty(const std::string &propertyName, glm::vec3 data);
        void SetProperty(const std::string &propertyName, glm::vec4 data);
        void SetProperty(const std::string &propertyName, glm::mat3 data);
        void SetProperty(const std::string &propertyName, glm::mat4 data);

    private:
        std::shared_ptr<ShaderProgram> _shader;
        std::unordered_map<std::string, MaterialProperty> _properties;
    };
}