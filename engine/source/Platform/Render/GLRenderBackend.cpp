#include <format>
#include <GL/gl3w.h>

#include <Engine/Logger.h>
#include <Platform/Render/GLRenderBackend.h>
#include <Platform/Render/GLContextSolver.h>

namespace TE
{
    GLRenderBackend::GLRenderBackend(int openGLMajorVersion, int openGLMinorVersion)
    {
        _renderApiType = OpenGL;
        _majorVersion = openGLMajorVersion;
        _minorVersion = openGLMinorVersion;
        Logger::Message(std::format("RenderBackend: GLRenderBackend {}.{}", openGLMajorVersion, openGLMinorVersion));
    }

    GLRenderBackend::~GLRenderBackend()
    {
        Logger::Message("RenderBackend: destroy");
    }

    bool GLRenderBackend::Init(const WindowBackend * const windowBackend)
    {
        Logger::Message("RenderBackend: init");

        if (!windowBackend)
        {
            Logger::Message("RenderBackend: window backend is null", Logger::Error);
            return false;
        }

        _context = std::unique_ptr<GLContext>(GLContextSolver::GetGLContext(windowBackend));

        if (_context == nullptr)
        {
            Logger::Message("RenderBackend: context solve fail", Logger::Error);
            return false;
        }

        if (!_context->Init(_majorVersion, _minorVersion))
        {
            Logger::Message("RenderBackend: context init fail", Logger::Error);
            return false;
        }

        _context->SetSwapInterval(0);

        return true;
    }

    void GLRenderBackend::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GLRenderBackend::ProcessSwapChain()
    {
        _context->ProcessSwapChain();
    }
}