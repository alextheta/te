#pragma once

#include <memory>

#include <Engine/Render/RenderBackend.h>
#include <Engine/Window/Window.h>
#include <Engine/Common.h>

namespace TE
{
    class TE_EXPORT Render
    {
    public:
        Render(RenderBackend * const backend);
        ~Render();
        bool Init(const Window * const window);

        void Clear();
        void ProcessSwapChain();

        static RenderApiType GetApiType();

    private:
        std::unique_ptr<RenderBackend> _renderBackend;
        inline static RenderApiType _renderApiType = Unknown;
    };
}
