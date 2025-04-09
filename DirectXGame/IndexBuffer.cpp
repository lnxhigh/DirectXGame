#include "IndexBuffer.h"

bool IndexBuffer::Init(ID3D11Device* device)
{
    m_device = device;

    return true;
}

bool IndexBuffer::Load(void* indices, UINT size_list)
{
    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = sizeof(UINT) * size_list;
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = indices;

    ComPtr<ID3D11Buffer> buffer = nullptr;
    HRESULT hr_buffer = m_device->CreateBuffer(&desc, &init_data, buffer.GetAddressOf());

    if (FAILED(hr_buffer))
    {
        OutputDebugStringA("Error: Failed to create an index buffer\n");
        return false;
    }

    m_index_buffer = buffer;

    return true;
}
