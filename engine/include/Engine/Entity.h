#pragma once

#include <boost/dynamic_bitset.hpp>

#include <Engine/Common.h>
#include <Engine/World.h>
#include <Engine/Component.h>

namespace TE
{
    class Entity final
    {
    public:
        static const int32_t InvalidIndex = -1;

        std::string name;

        Entity(int32_t id, int32_t version, const std::string &name);

        template<typename T>
        inline T *AddComponent()
        {
            return _world->AddComponent<T>(*this);
        }

        template<typename T>
        inline T *GetComponent()
        {
            return _world->GetComponent<T>(*this);
        }

        template<typename T>
        inline void RemoveComponent()
        {
            _world->RemoveComponent<T>(*this);
        }

    private:
        friend class World;

        friend class BaseFilter;

        int32_t _id;
        int32_t _version;
        boost::dynamic_bitset<> _components;
        World *_world;
    };
}