#include <Core/Render/Material.h>

namespace TE
{
    Material::Material(std::shared_ptr<ShaderProgram> &shader) : _shader(shader) // TODO: refactor somehow
    {
    }

    void Material::Bind()
    {
        _shader->Bind();

        for (auto property : _properties)
        {
            auto name = property.first;
            auto data = property.second.GetData();

            if (std::holds_alternative<bool>(data)) // bool
            {
                auto unpackedData = std::get<bool>(data);
                _shader->SetProperty(name, unpackedData);
            }
            else if (std::holds_alternative<int32_t>(data)) // int32_t
            {
                auto unpackedData = std::get<int32_t>(data);
                _shader->SetProperty(name, unpackedData);
            }
            else if (std::holds_alternative<float>(data)) // float
            {
                auto unpackedData = std::get<float>(data);
                _shader->SetProperty(name, unpackedData);
            }
            else if (std::holds_alternative<glm::vec2>(data)) // vec2
            {
                auto unpackedData = std::get<glm::vec2>(data);
                _shader->SetProperty(name, unpackedData);
            }
            else if (std::holds_alternative<glm::vec3>(data)) // vec3
            {
                auto unpackedData = std::get<glm::vec3>(data);
                _shader->SetProperty(name, unpackedData);
            }
            else if (std::holds_alternative<glm::vec4>(data)) // vec4
            {
                auto unpackedData = std::get<glm::vec4>(data);
                _shader->SetProperty(name, unpackedData);
            }
            else if (std::holds_alternative<glm::mat3>(data)) // mat3
            {
                auto unpackedData = std::get<glm::mat3>(data);
                _shader->SetProperty(name, unpackedData);
            }
            else if (std::holds_alternative<glm::mat4>(data)) // mat4
            {
                auto unpackedData = std::get<glm::mat4>(data);
                _shader->SetProperty(name, unpackedData);
            }
        }
    }

    bool Material::IsValid()
    {
        return _shader->IsValid();
    }

    void Material::SetProperty(const std::string &propertyName, bool data)
    {
        if (_shader->ContainsProperty(propertyName))
        {
            _properties[propertyName] = MaterialProperty(data);
        }
    }

    void Material::SetProperty(const std::string &propertyName, int32_t data)
    {
        if (_shader->ContainsProperty(propertyName))
        {
            _properties[propertyName] = MaterialProperty(data);
        }
    }

    void Material::SetProperty(const std::string &propertyName, float data)
    {
        if (_shader->ContainsProperty(propertyName))
        {
            _properties[propertyName] = MaterialProperty(data);
        }
    }

    void Material::SetProperty(const std::string &propertyName, glm::vec2 data)
    {
        if (_shader->ContainsProperty(propertyName))
        {
            _properties[propertyName] = MaterialProperty(data);
        }
    }

    void Material::SetProperty(const std::string &propertyName, glm::vec3 data)
    {
        if (_shader->ContainsProperty(propertyName))
        {
            _properties[propertyName] = MaterialProperty(data);
        }
    }

    void Material::SetProperty(const std::string &propertyName, glm::vec4 data)
    {
        if (_shader->ContainsProperty(propertyName))
        {
            _properties[propertyName] = MaterialProperty(data);
        }
    }

    void Material::SetProperty(const std::string &propertyName, glm::mat3 data)
    {
        if (_shader->ContainsProperty(propertyName))
        {
            _properties[propertyName] = MaterialProperty(data);
        }
    }

    void Material::SetProperty(const std::string &propertyName, glm::mat4 data)
    {
        if (_shader->ContainsProperty(propertyName))
        {
            _properties[propertyName] = MaterialProperty(data);
        }
    }
}