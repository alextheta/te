#include <uuid_v4.h>

#include <Engine/Entity.h>

#include <Core/Logger.h>
#include <format>

namespace TE
{
    Entity::Entity(std::string name, EntityId &entityId) : name(name)
    {
        std::memcpy(&id, &entityId, sizeof(id));
    }

    Entity::EntityId Entity::GetId() const
    {
        return id;
    }

    std::string Entity::GetIdString() const
    {
        auto uuid = UUID::UUID((char *) id.data);
        return uuid.str();
    }
}