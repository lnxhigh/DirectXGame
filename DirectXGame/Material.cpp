#include "Material.h"

bool Material::Init(ID3D11Device* device, const wchar_t* vs_path, const wchar_t* ps_path)
{
    // Vertex Shader

    if (!m_vertex_shader.Compile(vs_path))
        return false;

    if (!m_vertex_shader.Create(device))
        return false;

    // Pixel Shader

    if (!m_pixel_shader.Compile(ps_path))
        return false;

    if (!m_pixel_shader.Create(device))
        return false;

    // Input Layout

    ID3DBlob* vs_blob = m_vertex_shader.GetShaderBlob();
    if (!m_input_layout.Create(device, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize()))
        return false;

    // Material Buffer

    if (!m_material_buffer.Create(device))
        return false;

    // Now success

    return true;
}

void Material::Update(ID3D11DeviceContext* context)
{
    auto& material_data = m_material_buffer.Data();
    material_data.diffuse = m_diffuse;
    material_data.specular = m_specular;
    material_data.shininess = m_shininess;

    m_material_buffer.Update(context);
}

void Material::Bind(ID3D11DeviceContext* context)
{
    context->IASetInputLayout(m_input_layout.Get());
    context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
    context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);

    m_material_buffer.Bind(context, ShaderStage::Pixel, 2);
}
