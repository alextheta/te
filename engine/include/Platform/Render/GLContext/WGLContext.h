#pragma once

#include <Windows.h>

#include <Platform/Render/GLContext/GLContext.h>
#include <Platform/Window/Win32WindowHandle.h>

namespace TE
{
    class WGLContext final : public GLContext
    {
    public:
        WGLContext(const WindowHandle * const windowHandle);
        virtual ~WGLContext() override;
        virtual bool Init(int openGLMajorVersion, int openGLMinorVersion) override;

        virtual void SetSwapInterval(int interval)  override;
        virtual void ProcessSwapChain() override;

    private:
        bool InitExtensions();
        bool BindExtensions();

        const Win32WindowHandle *_windowHandle;
        HDC _displayContext;
        HGLRC _renderContext;
    };
}