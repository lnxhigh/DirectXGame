#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>

using namespace DirectX;
using Microsoft::WRL::ComPtr;

typedef struct MatrixBufferType
{
    XMMATRIX world;
    XMMATRIX view;
    XMMATRIX proj;

} MatrixBufferType;

class MatrixBuffer
{
private:
    MatrixBufferType m_data;
    ComPtr<ID3D11Buffer> m_buffer;

public:
    bool Create(ID3D11Device* device);

    const XMMATRIX& GetWorldMatrix() { return m_data.world; }
    const XMMATRIX& GetViewMatrix() { return m_data.view; }
    const XMMATRIX& GetProjectionMatrix() { return m_data.proj; }

    void SetWorldMatrix(const XMMATRIX& world) { m_data.world = world; }
    void SetViewMatrix(const XMMATRIX& view) { m_data.view = view; }
    void SetProjectionMatrix(const XMMATRIX& projection) { m_data.proj = projection; }

    ID3D11Buffer* Get() const { return m_buffer.Get(); }
    ID3D11Buffer** GetAddressOf() { return m_buffer.GetAddressOf(); }
};
