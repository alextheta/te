#pragma once

#include <Engine/Render/BufferLayout.h>

namespace TE
{
    class GLBufferLayout final : public BufferLayout
    {
    public:
        GLBufferLayout();
        ~GLBufferLayout();
    };
}