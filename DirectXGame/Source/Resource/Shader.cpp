#include "Resource/Shader.h"

bool Shader::Init(ID3D11Device* device, const ShaderDescriptor& descriptor)
{
    std::string vs_path = descriptor.vertex_shader_path;
    std::string ps_path = descriptor.pixel_shader_path;

    // Vertex Shader

    if (!m_vertex_shader.Compile(std::wstring(vs_path.begin(), vs_path.end()).c_str()))
        return false;

    if (!m_vertex_shader.Create(device))
        return false;

    // Pixel Shader

    if (!m_pixel_shader.Compile(std::wstring(ps_path.begin(), ps_path.end()).c_str()))
        return false;

    if (!m_pixel_shader.Create(device))
        return false;

    // Input Layout

    ID3DBlob* vs_blob = m_vertex_shader.GetShaderBlob();
    if (!m_input_layout.Create(device, vs_blob->GetBufferPointer(), vs_blob->GetBufferSize()))
        return false;

    // Now success

    return true;
}

void Shader::Bind(ID3D11DeviceContext* context)
{
    context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
    context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
    context->IASetInputLayout(m_input_layout.Get());
}
