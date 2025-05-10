#include "Resource/Material.h"

bool Material::Init(ID3D11Device* device)
{
    // Material Buffer

    if (!m_material_buffer.Create(device))
        return false;

    // Now success

    return true;
}

void Material::Update(ID3D11DeviceContext* context)
{
    auto& material_data = m_material_buffer.Data();
    material_data.diffuse = m_material_data.diffuse;
    material_data.specular = m_material_data.specular;
    material_data.shininess = m_material_data.shininess;

    m_material_buffer.Update(context);
}

void Material::Bind(ID3D11DeviceContext* context)
{
    shader->Bind(context);
    diffuse_map->Bind(context, 0);
    m_material_buffer.Bind(context, ShaderStage::Pixel, 2);
}
