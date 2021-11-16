#include <uuid_v4.h>
#include <format>

#include <Core/Logger.h>
#include <Engine/World.h>

namespace TE
{
    static UUID::UUIDGenerator<std::mt19937_64> uuidGenerator;

    World::World(std::string name) : name(name)
    {
        _components = std::make_unique<std::unordered_map<std::type_index, std::shared_ptr<EntityComponents>>>();
        _entities = std::make_unique<std::unordered_map<Entity::EntityId, std::shared_ptr<Entity>, EntityHash>>();

        Logger::Message(std::format("world \"{}\": instantiate", name));
    }

    World::~World()
    {
        Logger::Message(std::format("world \"{}\": destroy", name));
    }

    std::shared_ptr<Entity> World::AddEntity(std::string entityName)
    {
        Entity::EntityId entityId;
        UUID::UUID uuid = uuidGenerator.getUUID();
        std::memcpy(entityId.data, uuid.bytes().c_str(), sizeof(entityId.data));

        auto entity = std::make_shared<Entity>(entityName, entityId);

        _entities->insert({entityId, entity});

        return entity;
    }

    const std::shared_ptr<Component> World::AddComponent(std::shared_ptr<Entity> entity, std::shared_ptr<Component> component)
    {
        if (!EntityExists(entity))
        {
            return nullptr;
        }

        std::type_index componentType = typeid(*component);

        if (!_components->contains(componentType))
        {
            (*_components)[componentType] = std::make_shared<EntityComponents>();
        }

        auto entityId = entity->GetId();
        auto entityComponents = (*_components)[componentType];

        if (ComponentExists(entity, componentType))
        {
            return (*entityComponents)[entityId];
        }

        (*entityComponents)[entityId] = std::shared_ptr<Component>(component);
        return (*entityComponents)[entityId];
    }

    void World::RemoveComponent(std::shared_ptr<Entity> entity, std::type_index componentType)
    {
        if (!EntityExists(entity) || !ComponentExists(entity, componentType))
        {
            return;
        }

        auto entityId = entity->GetId();
        auto entityComponents = (*_components)[componentType];

        if (!entityComponents->contains(entityId))
        {
            return;
        }

        entityComponents->erase(entityId);
    }

    bool World::EntityExists(std::shared_ptr<Entity> entity) const
    {
        return _entities->contains(entity->GetId());
    }

    bool World::ComponentExists(std::shared_ptr<Entity> entity, std::type_index componentType) const
    {
        auto entityId = entity->GetId();

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