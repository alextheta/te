#pragma once

#include <unordered_map>
#include <unordered_set>
#include <typeindex>

#include <Core/Common.h>
#include <Engine/Entity.h>
#include <Engine/Components/Component.h>

namespace TE
{
    class TE_API World final
    {
    public:
        std::string name;

        World(std::string name);
        ~World();

        std::shared_ptr<Entity> AddEntity(std::string entityName);

        template<typename T>
        const std::shared_ptr<T> AddComponent(std::shared_ptr<Entity> entity)
        {
            if (!EntityExists(entity) || ComponentExists<T>(entity))
            {
                return nullptr;
            }

            auto component = std::make_shared<T>();
            return std::dynamic_pointer_cast<T>(AddComponent(entity, component));
        }

        template<typename T>
        void RemoveComponent(std::shared_ptr<Entity> entity)
        {
            RemoveComponent(entity, typeid(T));
        }

        bool EntityExists(std::shared_ptr<Entity> entity) const;

        template<typename T>
        bool ComponentExists(std::shared_ptr<Entity> entity) const
        {
            return ComponentExists(entity, typeid(T));
        }

    private:
        struct EntityHash
        {
            std::size_t operator()(const Entity::EntityId &entityId) const;
        };

        typedef std::unordered_map<Entity::EntityId, std::shared_ptr<Component>, EntityHash> EntityComponents;
        std::unique_ptr<std::unordered_map<std::type_index, std::shared_ptr<EntityComponents>>> _components;
        std::unique_ptr<std::unordered_map<Entity::EntityId, std::shared_ptr<Entity>, EntityHash>> _entities;

        const std::shared_ptr<Component> AddComponent(std::shared_ptr<Entity> entity, std::shared_ptr<Component> component);
        void RemoveComponent(std::shared_ptr<Entity> entity, std::type_index componentType);
        bool ComponentExists(std::shared_ptr<Entity> entity, std::type_index componentType) const;
    };
}