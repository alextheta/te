#pragma once

#include <Engine/Application.h>

namespace TE
{
    class EditorApp : public Application
    {
    public:
        void Init();
        void Update();
        void Dispose();
    };
}