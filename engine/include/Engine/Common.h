#pragma once

#include <cstdint>

namespace TE
{
    inline int32_t ComponentTypeCount = 0;

    template<typename T>
    static int32_t GetComponentTypeId()
    {
        static int32_t componentTypeId = ComponentTypeCount++;
        return componentTypeId;
    }
}