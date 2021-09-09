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
        void Run();

    private:
        std::unique_ptr<Window> _window;
        std::unique_ptr<Render> _render;
    };
}
