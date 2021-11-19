#include <uuid_v4.h>

#include <Engine/World.h>

namespace TE
{
    Entity::Entity(const std::string &name, EntityId &entityId, World *world) : name(name), _id(entityId), _world(world)
    {
    }

    Entity::EntityId Entity::GetId() const
    {
        return _id;
    }

    std::shared_ptr<Component> Entity::AddComponent(std::shared_ptr<Component> component)
    {
        if (_world == nullptr)
        {
            return nullptr;
        }

        return _world->AddComponent(_id, component);
    }

    std::shared_ptr<Component> Entity::GetComponent(std::type_index componentType) const
    {
        if (_world == nullptr)
        {
            return nullptr;
        }

        auto id = GetId();
        return _world->GetComponent(id, componentType);
    }

    void Entity::RemoveComponent(std::type_index componentType)
    {
        if (_world == nullptr)
        {
            return;
        }

        _world->RemoveComponent(_id, componentType);
    }

    bool Entity::CanAddComponent(std::type_index componentType)
    {
        if (_world == nullptr)
        {
            return false;
        }

        return _world->EntityExists(_id) && !_world->ComponentExists(_id, componentType);
    }

    std::string Entity::GetIdString() const
    {
        auto uuid = UUID::UUID((char *) _id.data);
        return uuid.str();
    }
}