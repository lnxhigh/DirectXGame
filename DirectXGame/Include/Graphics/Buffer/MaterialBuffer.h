#pragma once
#include <DirectXMath.h>

#include "Graphics/Buffer/ConstantBuffer.h"

using namespace DirectX;

struct alignas(16) MaterialBufferData
{
    XMFLOAT4 diffuse;
    XMFLOAT4 specular;
    XMFLOAT4 ambient;
    XMFLOAT4 emissive;

    float shininess;
    XMFLOAT3 padding_shininess; // 16-byte alignment
};

using MaterialBuffer = ConstantBuffer<MaterialBufferData>;
