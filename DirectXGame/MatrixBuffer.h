#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>

using namespace DirectX;
using Microsoft::WRL::ComPtr;

class MatrixBuffer
{
private:
    struct MatrixBufferType
    {
        XMMATRIX world;
        XMMATRIX view;
        XMMATRIX proj;
    };

    ComPtr<ID3D11Buffer> m_buffer;

public:
    bool Init(ID3D11Device* device);

    void SetMatrixData(
        ID3D11DeviceContext* context,
        const XMMATRIX& world, const XMMATRIX& view, const XMMATRIX& proj
    );

    ID3D11Buffer* GetMatrixBuffer() const { return m_buffer.Get(); }
    ID3D11Buffer** GetMatrixBufferAddress() { return m_buffer.GetAddressOf(); }
};
