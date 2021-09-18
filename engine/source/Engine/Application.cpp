#include <iostream>

//#include <memory>

#include <Engine/Application.h>
#include <Platform/Window/Win32WindowBackend.h>
#include <Platform/Render/GLRenderBackend.h>
#include <Engine/Logger.h>

namespace TE
{
    Application::Application()
    {
        new Logger(&std::cout, true, true);

        _engineCore = std::make_unique<TE::Core>(
                new Win32WindowBackend(),
                new GLRenderBackend(4, 6));
    }

    void Application::Run()
    {
        auto windowSettings = std::make_unique<WindowSettings>();
        windowSettings->title = L"te";
        windowSettings->width = 800;
        windowSettings->height = 600;

        _engineCore->Init(windowSettings.get());

        std::shared_ptr<Window> window = _engineCore->GetWindow();
        std::shared_ptr<Render> render = _engineCore->GetRender();

        window->WindowCloseEvent.AddListener(&Application::OnWindowClose, this);

        Init();

        _isRunning = true;
        while (_isRunning)
        {
            window->PollEvents();

            Update();
        }

        Dispose();
    }

    void Application::OnWindowClose()
    {
        _isRunning = false;
    }
}