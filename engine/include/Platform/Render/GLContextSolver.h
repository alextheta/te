#pragma once

#include <Engine/Render/RenderBackend.h>
#include <Platform/Render/GLContext/GLContext.h>

namespace TE
{
    class GLContextSolver
    {
    public:
        static GLContext *GetGLContext(WindowBackend *windowBackend);
    };
}