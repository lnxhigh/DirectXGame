#include "Graphics/Buffer/IndexBuffer.h"

bool IndexBuffer::Create(ID3D11Device* device, void* indices, UINT size_list)
{
    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = sizeof(UINT) * size_list;
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = indices;

    ComPtr<ID3D11Buffer> buffer = nullptr;
    HRESULT hr_buffer = device->CreateBuffer(&desc, &init_data, buffer.GetAddressOf());

    if (FAILED(hr_buffer))
    {
        OutputDebugStringA("Error: Failed to create an index buffer\n");
        return false;
    }

    m_buffer = buffer;
    m_index_count = size_list;

    return true;
}
