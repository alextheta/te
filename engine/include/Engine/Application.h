#pragma once

#include <Engine/Core.h>

namespace TE
{
    class Application
    {
    public:
        Application();
        virtual ~Application() = default;

        virtual void Run() final;
        virtual void OnWindowClose() final;

        virtual void Init() = 0;
        virtual void Update() = 0;
        virtual void Dispose() = 0;

        virtual const std::shared_ptr<Window> GetWindow() final;
        virtual const std::shared_ptr<Render> GetRender() final;

    private:
        std::unique_ptr<Core> _engineCore;
        bool _isRunning;
    };
}
