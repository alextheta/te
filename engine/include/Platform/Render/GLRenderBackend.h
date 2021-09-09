#pragma once

#include <Engine/Render/RenderBackend.h>
#include <Platform/Render/GLContext/GLContext.h>

namespace TE
{
    class GLRenderBackend : public RenderBackend
    {
    public:
        GLRenderBackend(int openGLMajorVersion, int openGLMinorVersion);
        ~GLRenderBackend();
        bool Init(WindowBackend *windowBackend);

        void Clear();
        void ProcessSwapChain();

    private:
        std::unique_ptr<GLContext> _context;
        int _majorVersion;
        int _minorVersion;
    };
}