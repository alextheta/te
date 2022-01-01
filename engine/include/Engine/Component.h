#pragma once

namespace TE
{
    class Component
    {
    public:

        Component()
        {

        }
        Component(const Component& other)
        {

        }

        virtual ~Component() = default;

        virtual Component& operator=(const Component& other)
        {
            return *this;
        }
    };
}
