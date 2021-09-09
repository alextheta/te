#pragma once

#include <Engine/Core.h>

namespace TE
{
    class Application
    {
    public:
        Application();
        ~Application();

        void Run();

    private:
        std::unique_ptr<Core> _engineCore;
    };
}
