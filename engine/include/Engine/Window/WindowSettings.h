#pragma once

#include <string>

#include <Engine/Common.h>

namespace TE
{
    class TE_API WindowSettings
    {
    public:
        std::wstring title;
        int width;
        int height;
    };
}