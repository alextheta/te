#include <uuid_v4.h>
#include <format>
#include <vector>

#include <Core/Logger.h>
#include <Engine/World.h>

namespace TE
{
    static UUID::UUIDGenerator<std::mt19937_64> uuidGenerator;

    World::World(const std::string &name) : name(name)
    {
        _components = std::make_unique<std::unordered_map<std::type_index, std::shared_ptr<EntityComponents>>>();
        _entities = std::make_unique<std::unordered_map<Entity::EntityId, std::shared_ptr<Entity>, EntityHash>>();

        Logger::Message(std::format("world \"{}\": instantiate", name));
    }

    World::~World()
    {
        Logger::Message(std::format("world \"{}\": destroy", name));
    }

    std::shared_ptr<Entity> World::CreateEntity(const std::string &entityName)
    {
        Entity::EntityId entityId;
        UUID::UUID uuid = uuidGenerator.getUUID();
        std::memcpy(entityId.data, uuid.bytes().c_str(), sizeof(entityId.data));

        auto entity = std::make_shared<Entity>(entityName, entityId, this);

        _entities->insert({entityId, entity});

        return entity;
    }

    std::shared_ptr<Entity> World::FindEntity(const std::string &entityName) const
    {
        for (auto entityIdPair : *_entities)
        {
            auto entity = entityIdPair.second;
            if (entityName.compare(entity->name) == 0)
            {
                return entity;
            }
        }

        return nullptr;
    }

    void World::DestroyEntity(std::shared_ptr<Entity> entity)
    {
        if (entity == nullptr)
        {
            return;
        }

        auto entityId = entity->GetId();
        DestroyEntity(entityId);
    }

    void World::DestroyEntity(Entity &entity)
    {
        auto entityId = entity.GetId();
        DestroyEntity(entityId);
    }

    void World::DestroyEntity(Entity::EntityId &entityId)
    {
        if (!EntityExists(entityId))
        {
            return;
        }

        RemoveAllComponents(entityId);
        _entities->erase(entityId);
    }

    bool World::EntityExists(std::shared_ptr<Entity> entity) const
    {
        if (entity == nullptr)
        {
            return false;
        }

        auto entityId = entity->GetId();
        return EntityExists(entityId);
    }

    bool World::EntityExists(Entity &entity) const
    {
        auto entityId = entity.GetId();
        return EntityExists(entityId);
    }

    bool World::EntityExists(Entity::EntityId &entityId) const
    {
        return _entities->contains(entityId);
    }

    std::shared_ptr<Component> World::AddComponent(Entity::EntityId &entityId, std::shared_ptr<Component> component)
    {
        if (!EntityExists(entityId))
        {
            return nullptr;
        }

        std::type_index componentType = typeid(*component);

        if (!_components->contains(componentType))
        {
            (*_components)[componentType] = std::make_shared<EntityComponents>();
        }

        auto entityComponents = (*_components)[componentType];

        if (ComponentExists(entityId, componentType))
        {
            return (*entityComponents)[entityId];
        }

        (*entityComponents)[entityId] = std::shared_ptr<Component>(component);
        return (*entityComponents)[entityId];
    }

    std::shared_ptr<Component> World::GetComponent(Entity::EntityId &entityId, std::type_index componentType) const
    {
        if (!ComponentExists(entityId, componentType))
        {
            return nullptr;
        }

        auto entityComponents = (*_components)[componentType];

        return (*entityComponents)[entityId];
    }

    void World::RemoveComponent(Entity::EntityId &entityId, std::type_index componentType)
    {
        if (!ComponentExists(entityId, componentType))
        {
            return;
        }

        auto entityComponents = (*_components)[componentType];

        if (!entityComponents->contains(entityId))
        {
            return;
        }

        entityComponents->erase(entityId);
    }

    void World::RemoveAllComponents(Entity::EntityId &entityId) // TODO: optimize & rework entity-component database
    {
        if (!EntityExists(entityId))
        {
            return;
        }

        std::vector<std::shared_ptr<Component>> componentsToRemove;

        for (auto componentEntityPair : *_components)
        {
            auto entityComponents = componentEntityPair.second;
            for (auto entityComponent : *entityComponents)
            {
                auto foundEntityId = entityComponent.first;
                if (foundEntityId != entityId)
                {
                    continue;
                }

                componentsToRemove.push_back(entityComponent.second);
            }
        }

        for (auto component : componentsToRemove)
        {
            RemoveComponent(entityId, typeid(*component));
        }
    }

    bool World::ComponentExists(Entity::EntityId &entityId, std::type_index componentType) const
    {
        if (!_entities->contains(entityId) || !_components->contains(componentType))
        {
            return false;
        }

        return (*_components)[componentType]->contains(entityId);
    }

    std::size_t World::EntityHash::operator()(const Entity::EntityId &entityId) const
    {
        return std::hash<int>()(entityId.data[0]) ^
               std::hash<int>()(entityId.data[1]) ^
               std::hash<int>()(entityId.data[2]) ^
               std::hash<int>()(entityId.data[3]);
    }
}