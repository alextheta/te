#pragma once

#include <Engine/Common.h>

namespace TE
{
    class TE_API WindowHandle
    {
    public:
        virtual ~WindowHandle() = default;
        virtual void * const GetRawHandle() const = 0;
    };
}