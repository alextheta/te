#pragma once

#include <Engine/Render/Render.h>
#include <Engine/Window/Window.h>

namespace TE
{
    class Core
    {
    public:
        Core(WindowBackend *windowBackend, RenderBackend *renderBackend);
        ~Core();

        bool Init(WindowSettings *windowSettings);

        std::shared_ptr<Window> GetWindow();
        std::shared_ptr<Render> GetRender();

    private:
        std::shared_ptr<Window> _window;
        std::shared_ptr<Render> _render;
    };
}
