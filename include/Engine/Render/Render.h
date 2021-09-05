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

        void Draw();

    private:
        std::unique_ptr<RenderBackend> _renderBackend;
    };
}
