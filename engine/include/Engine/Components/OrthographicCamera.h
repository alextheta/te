#pragma once

#include <Engine/Components/Camera.h>
#include <Core/Logger.h>

namespace TE
{
    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera()
        {
            Logger::Message("Orthographic camera create");
        }

        virtual ~OrthographicCamera() override
        {
            Logger::Message("Orthographic camera destroy");
        }
    };
}
