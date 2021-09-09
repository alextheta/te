#include <Platform/Render/GLContextSolver.h>
#include <Platform/Render/GLContext/WGLContext.h>
#include <Platform/Window/Win32WindowBackend.h>

namespace TE
{
    GLContext *GLContextSolver::GetGLContext(WindowBackend *windowBackend)
    {
        auto backend = dynamic_cast<Win32WindowBackend*>(windowBackend);

        if (backend)
        {
            return new WGLContext(backend->GetWindowHandle());
        }

        return nullptr;
    }
}