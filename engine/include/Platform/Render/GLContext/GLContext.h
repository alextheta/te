#pragma once

#include <Core/Window/WindowHandle.h>

namespace TE
{
    class GLContext
    {
    public:
        virtual ~GLContext() = default;
        virtual bool Init(int openGLMajorVersion, int openGLMinorVersion) = 0;

        virtual void SetSwapInterval(int interval) = 0;
        virtual void ProcessSwapChain() = 0;

    protected:
        virtual bool InitExtensions() = 0;
        virtual bool BindExtensions() = 0;
    };
}