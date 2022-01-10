#include <Engine/Components/Transform.h>

namespace TE
{
    Transform::Transform()
    {
        position = glm::vec3(0);
        rotation = glm::vec4(0);
        scale = glm::vec3(1);
        parent = nullptr;
    }
}