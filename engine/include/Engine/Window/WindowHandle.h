#pragma once

namespace TE
{
    class WindowHandle
    {
    public:
        virtual ~WindowHandle() = default;
        virtual void * const GetRawHandle() const = 0;
    };
}