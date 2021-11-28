#include <Core/Render/MaterialProperty.h>

namespace TE
{
    MaterialProperty::MaterialProperty(MaterialData data) : _data(data)
    {
    }

    void MaterialProperty::SetData(MaterialData &data)
    {
        _data = data;
    }

    MaterialProperty::MaterialData MaterialProperty::GetData()
    {
        return _data;
    }
}