#include "Graphics/Buffer/LightBuffer.h"

bool LightBuffer::Create(ID3D11Device* device)
{
    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.ByteWidth = sizeof(LightBufferData);
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    HRESULT hr = device->CreateBuffer(&desc, nullptr, &m_buffer);
    if (FAILED(hr))
    {
        OutputDebugStringA("Error: Failed to create LightBuffer\n");
        return false;
    }

    return true;
}