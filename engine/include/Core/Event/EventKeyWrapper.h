#pragma once

#include <cstddef>
#include <stdint.h>

namespace TE
{
    class EventKeyWrapper
    {
    public:
        EventKeyWrapper(uint8_t *callbackPtr, int32_t callbackSize, void *objectPtr);

        struct Hash
        {
            std::size_t operator()(const EventKeyWrapper &eventKeyWrapper) const;
        };

        bool operator==(const EventKeyWrapper &other) const;

    private:
        uint8_t *_callbackPtr;
        int32_t _callbackSize;
        void *_objectPtr;
    };
}