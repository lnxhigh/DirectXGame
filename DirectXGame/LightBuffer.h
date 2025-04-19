#pragma once
#include <DirectXMath.h>

#include "ConstantBuffer.h"

using namespace DirectX;

struct alignas(16) LightBufferData
{
    XMFLOAT4 color;
    XMFLOAT3 direction;
    float padding; // 16-byte alignment
    XMFLOAT4 ambient;
};

using LightBuffer = ConstantBuffer<LightBufferData>;
