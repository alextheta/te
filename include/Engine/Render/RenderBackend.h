#pragma once

#include <memory>

#include <Engine/Window/WindowBackend.h>

namespace TE
{
    class RenderBackend
    {
    public:
        virtual ~RenderBackend() = 0;
        virtual bool Init(WindowBackend *windowBackend) = 0;

        virtual void Clear() = 0;
        virtual void ProcessSwapChain() = 0;
    };
}