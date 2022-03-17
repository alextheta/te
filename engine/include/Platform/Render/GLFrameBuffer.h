#pragma once

#include <GL/gl3w.h>

#include <Core/Render/FrameBuffer.h>

namespace TE
{
    class GLFrameBuffer final : public FrameBuffer
    {
    public:
        GLFrameBuffer(const Settings &spec);
        virtual ~GLFrameBuffer();

        void Reset();

        virtual void Bind() override;
        virtual void Unbind() override;
        virtual bool IsValid() override;
        virtual uint32_t GetColorAttachmentId() override;

    private:
        GLuint _id;
        GLuint _colorAttachment, _depthAttachment;
    };
}