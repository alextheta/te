#pragma once

#include <Core/Render/RenderBackend.h>
#include <Platform/Render/GLContext/GLContext.h>

namespace TE
{
    class GLRenderBackend final: public RenderBackend
    {
    public:
        GLRenderBackend(int openGLMajorVersion, int openGLMinorVersion);
        virtual ~GLRenderBackend() override;
        virtual bool Init(const WindowBackend * const windowBackend) override;

        virtual void Clear() override;
        virtual void ProcessSwapChain() override;

    private:
        std::unique_ptr<GLContext> _context;
        int _majorVersion;
        int _minorVersion;
    };
}