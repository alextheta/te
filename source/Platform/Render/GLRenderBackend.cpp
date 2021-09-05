#include <format>
#include <GL/gl3w.h>

#include <Engine/Logger.h>
#include <Platform/Render/GLRenderBackend.h>
#include <Platform/Render/GLContextSolver.h>

namespace TE
{
    GLRenderBackend::GLRenderBackend(int openGLMajorVersion, int openGLMinorVersion)
    {
        _majorVersion = openGLMajorVersion;
        _minorVersion = openGLMinorVersion;
        Logger::Instance().Message(std::format("RenderBackend: GLRenderBackend {}.{}", openGLMajorVersion, openGLMinorVersion));
    }

    GLRenderBackend::~GLRenderBackend()
    {
        Logger::Instance().Message("RenderBackend: destroy");
    }

    bool GLRenderBackend::Init(WindowBackend *windowBackend)
    {
        Logger::Instance().Message("RenderBackend: init");

        if (!windowBackend)
        {
            Logger::Instance().Message("RenderBackend: window backend is null", Logger::Error);
            return false;
        }

        _context = std::unique_ptr<GLContext>(GLContextSolver::GetGLContext(windowBackend));

        if (_context == nullptr)
        {
            Logger::Instance().Message("RenderBackend: context solve fail", Logger::Error);
            return false;
        }

        if (!_context->Init(_majorVersion, _minorVersion))
        {
            Logger::Instance().Message("RenderBackend: context init fail", Logger::Error);
            return false;
        }

        return true;
    }

    void GLRenderBackend::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLRenderBackend::ProcessSwapChain()
    {
        _context->ProcessSwapChain();
    }
}