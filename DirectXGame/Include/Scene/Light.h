#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

#include "Graphics/Buffer/LightBuffer.h"

using namespace DirectX;

class Light 
{
private:
    LightBuffer m_light_buffer;

public:
    XMFLOAT4 diffuse;
    XMFLOAT4 specular;
    XMFLOAT4 ambient;

    XMFLOAT3 direction;

public:
    bool Init(ID3D11Device* device);
    void Update(ID3D11DeviceContext* context);
    void Bind(ID3D11DeviceContext* context);

};
