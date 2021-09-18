#pragma once

#include <functional>
#include <unordered_map>

#include <Engine/Event/EventKeyWrapper.h>

namespace TE
{
    template<typename TFunc>
    class Event;

    template<class ReturnType, class... Args>
    class Event<ReturnType(Args ...)> final
    {
    private:
        typedef ReturnType (*Callback)(Args ...);

        typedef std::pair<void *, void *> Key;
        std::unordered_map<EventKeyWrapper, std::function<ReturnType(Args ...)>, EventKeyWrapper::Hash> _events;

    public:
        void AddListener(Callback callback)
        {
            EventKeyWrapper eventWrapper((uint8_t *) callback, 0, nullptr);

            std::function event(callback);

            _events.insert({eventWrapper, event});
        }

        void RemoveListener(Callback callback)
        {
            EventKeyWrapper eventWrapper((uint8_t *) callback, 0, nullptr);
            _events.erase(eventWrapper);
        }

        template<typename TObject>
        void AddListener(ReturnType(TObject::*callback)(Args...), TObject *object)
        {
            uint32_t callbackSize = sizeof(callback);
            uint8_t *callbackPtr = new uint8_t[callbackSize];
            EventKeyWrapper eventWrapper(callbackPtr, callbackSize, object);
            std::memcpy(callbackPtr, (void *) &callback, callbackSize);

            std::function event([object, callback](Args &&...args)
                                {
                                    return (object->*callback)(std::forward<Args>(args)...);
                                });

            _events.insert({eventWrapper, event});
        }

        template<typename TObject>
        void RemoveListener(ReturnType(TObject::*callback)(Args...), TObject *object)
        {
            uint32_t callbackSize = sizeof(callback);
            uint8_t *callbackPtr = new uint8_t[callbackSize];
            EventKeyWrapper eventWrapper(callbackPtr, callbackSize, object);
            std::memcpy(callbackPtr, (void *) &callback, callbackSize);

            _events.erase(eventWrapper);
        }

        void operator()()
        {
            for (auto const&[id, event] : _events)
            {
                event();
            }
        }

        template<typename ...CallbackArgs>
        void operator()(CallbackArgs... args)
        {
            for (auto const&[id, event] : _events)
            {
                event(args...);
            }
        }
    };
}