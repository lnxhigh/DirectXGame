#include "MatrixBuffer.h"

bool MatrixBuffer::Init(ID3D11Device* device)
{
    D3D11_BUFFER_DESC desc = { };
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.ByteWidth = sizeof(MatrixBufferType);
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    // Create a matrix buffer

    HRESULT hr = device->CreateBuffer(&desc, nullptr, &m_buffer);
    
    if (FAILED(hr))
    {
        OutputDebugStringA("Error: Failed to create a matrix buffer\n");
        return false;
    }

    return true;
}

void MatrixBuffer::SetMatrixData(
    ID3D11DeviceContext* context,
    const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& projection)
{
    D3D11_MAPPED_SUBRESOURCE resource;

    if (SUCCEEDED(context->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
    {
        MatrixBufferType* ptr = reinterpret_cast<MatrixBufferType*>(resource.pData);
        ptr->world = XMMatrixTranspose(world);
        ptr->view = XMMatrixTranspose(view);
        ptr->projection = XMMatrixTranspose(projection);
        context->Unmap(m_buffer.Get(), 0);
    }
}
