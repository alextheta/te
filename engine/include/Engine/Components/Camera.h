#pragma once

#include <glm/glm.hpp>

#include <Engine/Component.h>

namespace TE
{
    class Camera : public Component
    {
    public:
        virtual ~Camera() = default;

    protected:
        glm::mat4 _projection;
        glm::mat4 _view;
    };
}
