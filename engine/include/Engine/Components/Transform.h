#pragma once

#include <memory>
#include <glm/glm.hpp>

#include <Engine/Component.h>

namespace TE
{
    class Transform final : public Component
    {
    public:
        glm::vec3 position;
        glm::vec4 rotation;
        glm::vec3 scale;
        std::shared_ptr<Transform> parent;

        Transform();
    };
}
