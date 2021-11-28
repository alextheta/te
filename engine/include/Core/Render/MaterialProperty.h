#pragma once

#include <typeindex>
#include <variant>
#include <glm/glm.hpp>

namespace TE
{
    class MaterialProperty
    {
    public:
        typedef std::variant<bool, int32_t, float, glm::vec2, glm::vec3, glm::vec4, glm::mat3, glm::mat4> MaterialData;

        MaterialProperty() = default;
        MaterialProperty(MaterialData data);

        void SetData(MaterialData &data);
        MaterialData GetData();

    private:
        MaterialData _data;
    };
}