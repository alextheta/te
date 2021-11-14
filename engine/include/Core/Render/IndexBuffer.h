#pragma once

#include <memory>

#include <Core/Common.h>

namespace TE
{
    class TE_API IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        virtual uint32_t GetCount() = 0;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual bool IsValid() = 0;

        static std::shared_ptr<IndexBuffer> Create(int32_t *indices, uint32_t count);
    };
}