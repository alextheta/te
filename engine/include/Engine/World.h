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

        World(const std::string &name);
        ~World();

        std::shared_ptr<Entity> CreateEntity(const std::string &entityName);
        std::shared_ptr<Entity> FindEntity(const std::string &entityName) const;
        void DestroyEntity(std::shared_ptr<Entity> entity);
        void DestroyEntity(Entity &entity);
        bool EntityExists(std::shared_ptr<Entity> entity) const;
        bool EntityExists(Entity &entity) const;

        template<typename T>
        std::shared_ptr<T> AddComponent(std::shared_ptr<Entity> entity)
        {
            if (entity == nullptr)
            {
                return nullptr;
            }

            return AddComponent<T>(*entity);
        }

        template<typename T>
        std::shared_ptr<T> AddComponent(Entity &entity)
        {
            if (!EntityExists(entity) || ComponentExists<T>(entity))
            {
                return nullptr;
            }

            auto component = std::make_shared<T>();
            return std::dynamic_pointer_cast<T>(AddComponent(entity, component));
        }

        template<typename T>
        void RemoveComponent(std::shared_ptr<Entity> &entity) const
        {
            if (entity == nullptr)
            {
                return;
            }

            RemoveComponent(entity->GetId(), typeid(T));
        }

        template<typename T>
        void RemoveComponent(Entity &entity)
        {
            RemoveComponent(entity.GetId(), typeid(T));
        }

        template<typename T>
        std::shared_ptr<T> GetComponent(std::shared_ptr<Entity> entity) const
        {
            if (entity == nullptr)
            {
                return nullptr;
            }

            auto entityId = entity->GetId();
            return std::dynamic_pointer_cast<T>(GetComponent(entityId, typeid(T)));
        }

        template<typename T>
        std::shared_ptr<T> GetComponent(Entity &entity)
        {
            return GetComponent(entity.GetId(), typeid(T));
        }

        template<typename T>
        bool ComponentExists(std::shared_ptr<Entity> entity) const
        {
            if (entity == nullptr)
            {
                return;
            }

            return ComponentExists(entity->GetId(), typeid(T));
        }

        template<typename T>
        bool ComponentExists(Entity &entity) const
        {
            return ComponentExists(entity.GetId(), typeid(T));
        }

    private:
        friend class Entity;

        struct EntityHash
        {
            std::size_t operator()(const Entity::EntityId &entityId) const;
        };

        typedef std::unordered_map<Entity::EntityId, std::shared_ptr<Component>, EntityHash> EntityComponents;
        std::unique_ptr<std::unordered_map<std::type_index, std::shared_ptr<EntityComponents>>> _components;
        std::unique_ptr<std::unordered_map<Entity::EntityId, std::shared_ptr<Entity>, EntityHash>> _entities;

        void DestroyEntity(Entity::EntityId &entityId);
        bool EntityExists(Entity::EntityId &entityId) const;

        std::shared_ptr<Component> AddComponent(Entity::EntityId &entityId, std::shared_ptr<Component> component);
        std::shared_ptr<Component> GetComponent(Entity::EntityId &entityId, std::type_index componentType) const;
        void RemoveComponent(Entity::EntityId &entityId, std::type_index componentType);
        void RemoveAllComponents(Entity::EntityId &entity);
        bool ComponentExists(Entity::EntityId &entityId, std::type_index componentType) const;
    };
}