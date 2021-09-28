#pragma once

#include <Engine/Render/Render.h>
#include <Engine/Window/Window.h>
#include <Engine/Common.h>

namespace TE
{
    class TE_API Core
    {
    public:
        Core(WindowBackend *windowBackend, RenderBackend *renderBackend);
        ~Core();

        bool Init(WindowSettings &windowSettings);

        const std::shared_ptr<Window> GetWindow();
        const std::shared_ptr<Render> GetRender();

    private:
        std::shared_ptr<Window> _window;
        std::shared_ptr<Render> _render;
    };
}
