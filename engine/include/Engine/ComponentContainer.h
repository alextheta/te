#pragma once

namespace TE
{
    class Component;

    class BaseContainer
    {
    public:
        virtual void Set(std::size_t componentId, Component *component) = 0;
        virtual Component *const Get(std::size_t componentTypeId) = 0;
    };

    template<class T>
    class ComponentContainer final : public BaseContainer
    {
    public:
        ComponentContainer(int32_t initialCapacity)
        {
            _components.reserve(initialCapacity);
        }

        void Set(std::size_t componentId, Component *component) override
        {
            if (_sparseIndices.size() <= componentId)
            {
                _sparseIndices.resize(componentId + 1);
            }

            _sparseIndices[componentId] = _components.size();
            _components.push_back(*static_cast<T *>(component));
        }

        Component *const Get(std::size_t idx) override
        {
            return &_components[_sparseIndices[idx]];
        }

    private:
        std::vector<T> _components;
        std::vector<int32_t> _sparseIndices;
    };
}