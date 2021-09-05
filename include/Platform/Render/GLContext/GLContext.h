#pragma once

#include <Engine/Window/WindowHandle.h>

namespace TE
{
    class GLContext
    {
    public:
        GLContext(TE::WindowHandle *windowHandle);
        virtual ~GLContext() = 0;
        virtual bool Init(int openGLMajorVersion, int openGLMinorVersion) = 0;

        virtual void SetSwapInterval(int interval) = 0;
        virtual void ProcessSwapChain() = 0;

    protected:
        virtual bool InitExtensions() = 0;
        virtual bool BindExtensions() = 0;
    };
}