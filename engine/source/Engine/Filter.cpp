#include <Engine/Filter.h>

namespace TE
{
    BaseFilter::Iterator::Iterator(World *world, int32_t entityIndex, boost::dynamic_bitset<> components) : _world(world), _entityIndex(entityIndex), _components(components)
    {
    }

    BaseFilter::Iterator::Iterator()
    {
    }

    const BaseFilter::Iterator BaseFilter::begin() const
    {
        for (auto &entity : *_world->GetEntityPool())
        {
            auto entityComponents = entity._components;
            entityComponents.resize(_components.size());
            if ((_components & entityComponents) == _components)
            {
                return Iterator(_world, entity._id, _components);
            }
        }

        return Iterator(_world, _world->GetEntityPool()->size(), _components);
    }

    const BaseFilter::Iterator BaseFilter::end() const
    {
        return Iterator(_world, _world->GetEntityPool()->size(), _components);
    }

    Entity BaseFilter::Iterator::operator*() const
    {
        return (*_world->GetEntityPool())[_entityIndex];
    }

    bool BaseFilter::Iterator::operator==(const Iterator &other) const
    {
        return _entityIndex == other._entityIndex || _entityIndex == _world->GetEntityPool()->size();
    }

    bool BaseFilter::Iterator::operator!=(const Iterator &other) const
    {
        return _entityIndex != other._entityIndex && _entityIndex != _world->GetEntityPool()->size();
    }

    BaseFilter::Iterator &BaseFilter::Iterator::operator++()
    {
        while (true)
        {
            _entityIndex++;
            if (_entityIndex >= _world->GetEntityPool()->size() || IsValid())
            {
                break;
            }
        }

        return *this;
    }

    bool BaseFilter::Iterator::ComponentsMatch(const boost::dynamic_bitset<> &components) const
    {
        return _components.any() && components.any() && components == (_components & components);
    }

    bool BaseFilter::Iterator::IsValid()
    {
        auto entity = (*_world->GetEntityPool())[_entityIndex];
        return _world->IsEntityValid(entity) && ComponentsMatch(entity._components);
    }
}