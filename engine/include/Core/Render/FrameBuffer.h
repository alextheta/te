#pragma once

#include <memory>

#include <Core/Common.h>

namespace TE
{
    class TE_API FrameBuffer
    {
    public:
        class Settings
        {
        public:
            uint32_t width, height;
        };

        FrameBuffer(const Settings &spec);
        virtual ~FrameBuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual bool IsValid() = 0;

        virtual uint32_t GetColorAttachmentId() = 0;

        static std::shared_ptr<FrameBuffer> Create(const Settings &spec);

    protected:
        Settings _settings;
    };
}