#pragma once

#include <stdint.h>

#include <Core/Common.h>
#include <Engine/Components/Component.h>

namespace TE
{
    class TE_API Entity final
    {
    public:
        struct EntityId
        {
            int32_t data[4];

            bool operator==(const EntityId &rhs) const
            {
                return std::memcmp(data, rhs.data, sizeof(data)) == 0;
            }
        };

        std::string name;

        Entity(std::string name, EntityId &entityId);

        EntityId GetId() const;
        std::string GetIdString() const;

    private:
        EntityId id;
    };
}
