#pragma once

#include <memory>

#include <Engine/Window/WindowBackend.h>

namespace TE
{
    enum RenderApiType
    {
        Unknown,
        OpenGL
    };

    class RenderBackend
    {
    public:
        virtual ~RenderBackend() = default;
        virtual bool Init(WindowBackend *windowBackend) = 0;

        virtual void Clear() = 0;
        virtual void ProcessSwapChain() = 0;

        inline RenderApiType GetApiType() { return _renderApiType; };

    protected:
        RenderApiType _renderApiType;
    };
}