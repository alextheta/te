#pragma once

#include <string>

#include <Core/Common.h>

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