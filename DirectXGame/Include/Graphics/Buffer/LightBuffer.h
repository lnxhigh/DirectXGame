#pragma once
#include <DirectXMath.h>

#include "Graphics/Buffer/ConstantBuffer.h"

using namespace DirectX;

struct alignas(16) LightBufferData
{
    XMFLOAT4 diffuse;
    XMFLOAT4 specular;
    XMFLOAT4 ambient;

    XMFLOAT3 direction;
    float padding; // 16-byte alignment
};

using LightBuffer = ConstantBuffer<LightBufferData>;
