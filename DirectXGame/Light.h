#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

#include "LightBuffer.h"

using namespace DirectX;

class Light 
{
private:
    LightBuffer m_light_buffer;

private:
    XMFLOAT4 m_color;
    XMFLOAT3 m_direction;
    XMFLOAT4 m_ambient;

public:
    bool Init(ID3D11Device* device);
    void Update(ID3D11DeviceContext* context);
    void Bind(ID3D11DeviceContext* context);

public:
    const XMFLOAT4& GetColor() const { return m_color; }
    const XMFLOAT3& GetDirection() const { return m_direction; }
    const XMFLOAT4& GetAmbient() const { return m_ambient; }

    void SetColor(XMFLOAT4 color) { m_color = color; }
    void SetDirection(XMFLOAT3 direction) { m_direction = direction; }
    void SetAmbient(XMFLOAT4 ambient) { m_ambient = ambient; }
};
