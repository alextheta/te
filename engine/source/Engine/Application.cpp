#include <iostream>

#include <Engine/Application.h>
#include <Platform/Window/Win32WindowBackend.h>
#include <Platform/Render/GLRenderBackend.h>
#include <Engine/Logger.h>

namespace TE
{
    Application::Application()
    {
        auto logger = new Logger(&std::cout, true, true);
    }

    void Application::Run()
    {
        auto windowSettings = std::make_unique<WindowSettings>();
        windowSettings->title = L"te";
        windowSettings->width = 800;
        windowSettings->height = 600;

        auto core = std::make_unique<TE::Core>(
                new Win32WindowBackend(),
                new GLRenderBackend(4, 6));

        if (core->Init(windowSettings.get()))
        {
            core->Run();
        }
    }

    Application::~Application()
    {

    }
}