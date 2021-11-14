#pragma once

#include <Core/Render/RenderBackend.h>
#include <Platform/Render/GLContext/GLContext.h>

namespace TE
{
    class GLContextSolver
    {
    public:
        static GLContext *GetGLContext(const WindowBackend * const windowBackend);
    };
}