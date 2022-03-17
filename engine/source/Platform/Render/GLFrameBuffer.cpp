#include <Core/Logger.h>
#include <Platform/Render/GLFrameBuffer.h>

namespace TE
{
    GLFrameBuffer::GLFrameBuffer(const Settings &spec) : FrameBuffer(spec)
    {
        Reset();
    }

    GLFrameBuffer::~GLFrameBuffer()
    {
        glDeleteFramebuffers(1, &_id);
    }

    void GLFrameBuffer::Reset()
    {
        glCreateFramebuffers(1, &_id);
        glBindFramebuffer(GL_FRAMEBUFFER, _id);

        glCreateTextures(GL_TEXTURE_2D, 1, &_colorAttachment);
        glBindTexture(GL_TEXTURE_2D, _colorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _settings.width, _settings.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorAttachment, 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &_depthAttachment);
        glBindTexture(GL_TEXTURE_2D, _depthAttachment);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _settings.width, _settings.height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depthAttachment, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            Logger::Message("FrameBuffer: unable to create", Logger::Error);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void GLFrameBuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, _id);
    }

    void GLFrameBuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    bool GLFrameBuffer::IsValid()
    {
        return true;
    }

    uint32_t GLFrameBuffer::GetColorAttachmentId()
    {
        return _colorAttachment;
    }
}