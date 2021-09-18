#include <string>

#include <Engine/Event/EventKeyWrapper.h>

namespace TE
{
    std::size_t EventKeyWrapper::Hash::operator()(const EventKeyWrapper &eventKeyWrapper) const
    {
        std::string s((char *) eventKeyWrapper._callbackPtr, eventKeyWrapper._callbackSize);
        std::size_t h1 = std::hash<std::string> {}(s);
        std::size_t h2 = std::hash<void *> {}(eventKeyWrapper._objectPtr);
        return h1 ^ (h2 << 1);
    }

    EventKeyWrapper::EventKeyWrapper(uint8_t *callbackPtr, int32_t callbackSize, void *objectPtr)
            : _callbackPtr(callbackPtr), _callbackSize(callbackSize), _objectPtr(objectPtr)
    {
    }

    bool EventKeyWrapper::operator==(const EventKeyWrapper &other) const
    {
        if (&other == nullptr)
        {
            return false;
        }

        return (_objectPtr == nullptr || _callbackSize == 0 || other._objectPtr == nullptr || other._callbackSize == 0)
               ? _callbackPtr == other._callbackPtr
               : std::memcmp(_callbackPtr, other._callbackPtr, _callbackSize) == 0;
    }
}