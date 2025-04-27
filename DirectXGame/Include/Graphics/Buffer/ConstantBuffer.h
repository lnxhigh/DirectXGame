#pragma once
#include <cstring>

#include <d3d11.h>
#include <wrl/client.h>

#include "Graphics/Shader/ShaderStage.h"

template <typename T>
class ConstantBuffer
{
private:
    T m_data = {}; // CPU-side data
    Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;

public:
    // Create Buffer

    bool Create(ID3D11Device* device)
    {
        D3D11_BUFFER_DESC desc = {};
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.ByteWidth = sizeof(T);
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

        HRESULT hr = device->CreateBuffer(&desc, nullptr, &m_buffer);
        if (FAILED(hr))
        {
            OutputDebugStringA("Error: Failed to create a constant buffer\n");
            return false;
        }
        
        return true;
    }

    // Update data ( CPU-side -> GPU )

    void Update(ID3D11DeviceContext* context)
    {
        D3D11_MAPPED_SUBRESOURCE resource;
        HRESULT hr = context->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
        
        if (SUCCEEDED(hr))
        {
            std::memcpy(resource.pData, &m_data, sizeof(T));
            context->Unmap(m_buffer.Get(), 0);
        }
    }

    // Bind

    void Bind(ID3D11DeviceContext* context, ShaderStage stage, UINT slot)
    {
        ID3D11Buffer* buffer = m_buffer.Get();

        switch (stage)
        {
        case ShaderStage::Vertex:
            context->VSSetConstantBuffers(slot, 1, &buffer);
            break;
        case ShaderStage::Pixel:
            context->PSSetConstantBuffers(slot, 1, &buffer);
            break;
        case ShaderStage::Geometry:
            context->GSSetConstantBuffers(slot, 1, &buffer);
            break;
        case ShaderStage::Hull:
            context->HSSetConstantBuffers(slot, 1, &buffer);
            break;
        case ShaderStage::Domain:
            context->DSSetConstantBuffers(slot, 1, &buffer);
            break;
        case ShaderStage::Compute:
            context->CSSetConstantBuffers(slot, 1, &buffer);
            break;
        default:
            assert(false && "Invalid shader stage");
            break;
        }
    }

    // Data
    
    T& Data() { return m_data; }
    const T& Data() const { return m_data; }
    ID3D11Buffer* Get() const { return m_buffer.Get(); }
    ID3D11Buffer** GetAddressOf() const { return m_buffer.GetAddressOf(); }
};
