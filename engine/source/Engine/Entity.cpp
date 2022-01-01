#include <Engine/Entity.h>

namespace TE
{
    Entity::Entity(int32_t id, int32_t version, const std::string &name) : _id(id), _version(version), name(name)
    {
        _components.reset();
    }
}