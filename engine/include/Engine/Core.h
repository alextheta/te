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

        Window *const GetWindow();
        Render *const GetRender();

    private:
        std::unique_ptr<Window> _window;
        std::unique_ptr<Render> _render;
    };
}
