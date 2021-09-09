#pragma once

#include <memory>

#include <Engine/Render/RenderBackend.h>
#include <Engine/Window/Window.h>

namespace TE
{
    class Render
    {
    public:
        Render(RenderBackend *backend);
        ~Render();
        bool Init(Window *window);

        void Clear();
        void Draw();

        inline static RenderApiType GetApiType() { return _renderApiType; };

    private:
        std::unique_ptr<RenderBackend> _renderBackend;
        inline static RenderApiType _renderApiType = Unknown;
    };
}
