#include <Platform/Render/GLContextSolver.h>
#include <Platform/Render/GLContext/WGLContext.h>
#include <Platform/Window/Win32WindowBackend.h>

namespace TE
{
    GLContext *GLContextSolver::GetGLContext(const WindowBackend * const windowBackend)
    {
        auto platformWindowBackend = dynamic_cast<const Win32WindowBackend * const>(windowBackend);

        if (platformWindowBackend)
        {
            return new WGLContext(platformWindowBackend->GetWindowHandle());
        }

        return nullptr;
    }
}