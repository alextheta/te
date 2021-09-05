#pragma once

namespace TE
{
    class WindowHandle
    {
    public:
        virtual ~WindowHandle() = 0;
        virtual void *GetHandle() = 0;
    };
}