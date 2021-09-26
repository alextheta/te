#pragma once

namespace TE
{
    class WindowHandle
    {
    public:
        virtual ~WindowHandle() = default;
        virtual void *GetRawHandle() = 0;
    };
}