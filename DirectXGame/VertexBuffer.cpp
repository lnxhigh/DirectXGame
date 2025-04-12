#include "VertexBuffer.h"
#include <stddef.h>

bool VertexBuffer::Create(ID3D11Device* device, void* vertices, UINT size_vertex, UINT size_list)
{
    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = size_vertex * size_list;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = vertices;

    ComPtr<ID3D11Buffer> buffer = nullptr;
    HRESULT hr = device->CreateBuffer(&desc, &init_data, buffer.GetAddressOf());

    if (FAILED(hr))
    {
        OutputDebugStringA("Error: Failed to create a vertex buffer\n");
        return false;
    }

    m_buffer = buffer;
    m_stride = size_vertex;
    m_offset = 0;

    return true;
}
