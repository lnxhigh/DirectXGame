#include "VertexBuffer.h"
#include "Vertex.h"
#include <stddef.h>

bool VertexBuffer::Init(ID3D11Device* device)
{
    m_device = device;
    
    return true;
}

bool VertexBuffer::Load(void* vertices, UINT size_vertex, UINT size_list,
    void* shader_byte_code, SIZE_T size_byte_code)
{
    D3D11_BUFFER_DESC desc = { };
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = size_vertex * size_list;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = { };
    init_data.pSysMem = vertices;

    ComPtr<ID3D11Buffer> buffer = nullptr;
    HRESULT hr_buffer = m_device->CreateBuffer(&desc, &init_data, buffer.GetAddressOf());

    if (FAILED(hr_buffer))
    {
        return false;
    }

    // Create the vertex input layout
    // SemanticName - SemanticIndex - Format - InputSlot -  AlignedByteOffset - 
    // InputSlotClass - InstanceDataStepRate

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, color), D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    ComPtr<ID3D11InputLayout> input_layout = nullptr;
    HRESULT hr_layout = m_device->CreateInputLayout(layout, ARRAYSIZE(layout),
        shader_byte_code, size_byte_code, input_layout.GetAddressOf());

    if (FAILED(hr_layout))
    {
        return false;
    }

    m_vertex_buffer = buffer;
    m_input_layout = input_layout;

    return true;
}
