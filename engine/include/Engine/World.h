#pragma once

#include <vector>
#include <bitset>
#include <memory>
#include <stack>

#include <Engine/ComponentContainer.h>

namespace TE
{
    class Entity;

    class World final
    {
    public:
        World(const std::string &name);
        ~World();

        Entity CreateEntity(const std::string &name);
        void DestroyEntity(Entity &entity);
        bool IsEntityValid(Entity &entity);

        template<typename T>
        T *AddComponent(Entity &entity)
        {
            int32_t componentId = GetComponentTypeId<T>();
            if (_components.size() <= componentId)
            {
                CreateComponentContainer<T>(componentId);
            }

            return static_cast<T *>(AddComponent(entity, componentId, new T()));
        }

        template<typename T>
        T *GetComponent(Entity &entity)
        {
            return static_cast<T *>(GetComponent(entity, GetComponentTypeId<T>()));
        }

        template<typename T>
        void RemoveComponent(Entity &entity)
        {
            RemoveComponent(entity, GetComponentTypeId<T>());
        }

        const std::vector<Entity> *GetEntityPool() const;
        bool EntityExists(int index) const;

    private:
        std::string _name;
        int32_t _initialEntityPoolCapacity;
        int32_t _initialComponentPoolCapacity;
        int32_t _activeEntityCount = 0;
        std::vector<Entity> _entities;
        std::vector<int32_t> _entitySparseIndices;
        std::stack<int32_t> _unusedEntityIndexPool;
        std::vector<std::shared_ptr<BaseContainer>> _components;

        Component *AddComponent(Entity &entity, int32_t componentId, Component *component);
        Component *GetComponent(Entity &entity, int32_t componentId);
        void RemoveComponent(Entity &entity, int32_t componentId);

        template<typename T>
        void CreateComponentContainer(int32_t componentId)
        {
            auto componentContainer = std::make_shared<ComponentContainer<T>>(_initialComponentPoolCapacity);
            _components.push_back(componentContainer);
        }
    };
}