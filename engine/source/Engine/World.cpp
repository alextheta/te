#include <format>

#include <Engine/Entity.h>
#include <Core/Logger.h>

namespace TE
{
    World::World(const std::string &name) : _name(name)
    {
        _initialEntityPoolCapacity = 512;
        _initialComponentPoolCapacity = 128;

        Logger::Message(std::format("World \"{}\": instantiate", _name));
        _entitySparseIndices.reserve(_initialEntityPoolCapacity);
        _entities.reserve(_initialEntityPoolCapacity);
    }

    World::~World()
    {
        Logger::Message(std::format("World \"{}\": destroy", _name));
    }

    bool World::EntityExists(int index) const
    {
        if (index < _activeEntityCount && _entities[index]._id != Entity::InvalidIndex)
        {
            return true;
        }

        return false;
    }

    Entity World::CreateEntity(const std::string &name)
    {
        int entityId;

        if (!_unusedEntityIndexPool.empty())
        {
            entityId = _unusedEntityIndexPool.top();
            _unusedEntityIndexPool.pop();
        }
        else
        {
            entityId = _entities.size();
        }

        if (_entitySparseIndices.size() < entityId + 1)
        {
            _entitySparseIndices.resize(entityId + 1);
        }

        if (EntityExists(entityId))
        {
            return Entity(Entity::InvalidIndex, 0, "");
        }

        if (entityId < _entities.size())
        {
            int denseIndex = _entitySparseIndices[entityId];
            _entities[entityId]._id = denseIndex;
            _entities[entityId]._version++;
            _entities[entityId].name = name;
            _entities[entityId]._components.reset();
            _entitySparseIndices[denseIndex] = entityId;
        }
        else
        {
            _entities.push_back(Entity({entityId, 0, name}));
            _entitySparseIndices[entityId] = _entities.size() - 1;
        }

        //_entities[entityId]._components.clear();
        _entities[entityId]._world = this;
        _activeEntityCount++;

        return _entities[entityId];
    }

    void World::DestroyEntity(Entity &entity)
    {
        int entityId = entity._id;
        if (!EntityExists(entityId))
        {
            return;
        }

        int denseIndex = _entitySparseIndices[entityId];
        auto &temp = _entities[_activeEntityCount - 1];
        _entities[denseIndex] = temp;
        _entitySparseIndices[temp._id] = _entitySparseIndices[entityId];

        _activeEntityCount--;
        _unusedEntityIndexPool.push(temp._id);
        _entitySparseIndices[entityId] = -1;
        temp._id = Entity::InvalidIndex;
        temp._version++;
    }

    bool World::IsEntityValid(Entity &entity)
    {
        return entity._id != -1;
    }

    Component *World::AddComponent(Entity &entity, int32_t componentId, Component *component)
    {
        auto entityId = entity._id;
        auto &componentContainer = _components[componentId];
        componentContainer->Set(entityId, component);
        auto &entityComponents = _entities[entityId]._components;
        if (entityComponents.size() <= componentId)
        {
            entityComponents.resize(componentId + 1);
        }
        entityComponents.set(componentId);
        return componentContainer->Get(entityId);
    }

    Component *World::GetComponent(Entity &entity, int32_t componentId)
    {
        auto entityId = entity._id;
        auto &entityComponents = _entities[entityId]._components;
        if (entityComponents.size() <= componentId || !entityComponents.test(componentId))
        {
            return nullptr;
        }

        return _components[componentId]->Get(entityId);
    }

    void World::RemoveComponent(Entity &entity, int32_t componentId)
    {
        auto entityId = entity._id;
        if (_entities[entityId]._id != entityId)
        {
            return;
        }

        _entities[entityId]._components.reset(componentId);
    }

    const std::vector<Entity> *World::GetEntityPool() const
    {
        return &_entities;
    }
}