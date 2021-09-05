#include <iostream>

#include <Engine/Logger.h>
#include <Engine/Core.h>
#include <Platform/Window/Win32WindowBackend.h>
#include <Platform/Render/GLRenderBackend.h>

int main()
{
    TE::Logger::Instance().SetOutputStream(&std::cout);
    TE::Logger::Instance().SetSeverityPrinting(true);
    TE::Logger::Instance().SetTimePrinting(true);

    auto windowSettings = std::make_unique<TE::WindowSettings>();
    windowSettings->title = L"te";
    windowSettings->width = 800;
    windowSettings->height = 600;

    auto core = std::make_unique<TE::Core>(
            new TE::Win32WindowBackend(),
            new TE::GLRenderBackend(4, 6));

    if (core->Init(windowSettings.get()))
    {
        core->Run();
    }

    return 0;
}