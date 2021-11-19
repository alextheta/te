#pragma once

#include <typeindex>
#include <stdint.h>

#include <Core/Common.h>
#include <Engine/Components/Component.h>

namespace TE
{
    class World;

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

        Entity(const std::string &name, EntityId &entityId, World *world);

        template<typename T>
        std::shared_ptr<T> AddComponent()
        {
            if (!CanAddComponent(typeid(T)))
            {
                return nullptr;
            }

            auto component = std::make_shared<T>();
            return std::dynamic_pointer_cast<T>(AddComponent(component));
        }

        template<typename T>
        std::shared_ptr<T> GetComponent() const
        {
            return std::dynamic_pointer_cast<T>(GetComponent(typeid(T)));
        }

        template<typename T>
        void RemoveComponent()
        {
            RemoveComponent(typeid(T));
        }

        EntityId GetId() const;
        std::string GetIdString() const;

    private:
        EntityId _id;
        World *_world; // TODO: use smart ptr

        std::shared_ptr<Component> AddComponent(std::shared_ptr<Component> component);
        std::shared_ptr<Component> GetComponent(std::type_index componentType) const;
        void RemoveComponent(std::type_index componentType);
        bool CanAddComponent(std::type_index componentType);
    };
}
