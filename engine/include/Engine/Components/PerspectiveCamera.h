#pragma once

#include <Engine/Components/Camera.h>
#include <Core/Logger.h>

namespace TE
{
    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera()
        {
            Logger::Message("Perspective camera create");
        }

        virtual ~PerspectiveCamera() override
        {
            Logger::Message("Perspective camera destroy");
        }
    };
}
