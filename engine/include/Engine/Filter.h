#pragma once

#include <Engine/Entity.h>

namespace TE
{
    class BaseFilter
    {
    public:
        class Iterator
        {
        public:
            Iterator(World *world, int32_t entityIndex, boost::dynamic_bitset<> components);
            Iterator();

            bool IsValid();
            bool operator==(const Iterator &other) const;
            bool operator!=(const Iterator &other) const;
            Entity operator*() const;
            Iterator &operator++();

        private:
            int32_t _entityIndex;
            boost::dynamic_bitset<> _components;
            World *_world;
        };

        static bool ComponentsMatch(const boost::dynamic_bitset<> &leftComponents, const boost::dynamic_bitset<> &rightComponents);

        const Iterator begin() const;
        const Iterator end() const;

    protected:
        boost::dynamic_bitset<> _components;
        World *_world;
    };

    template<typename... ComponentTypes>
    class Filter final : public BaseFilter
    {
    public:
        Filter(World *world)
        {
            _world = world;
            _components.resize(sizeof...(ComponentTypes) + 1);
            for (auto componentId : {0, GetComponentTypeId<ComponentTypes>() ...})
            {
                _components.set(componentId);
            }
        }
    };
}