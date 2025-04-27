#pragma once
#include <DirectXMath.h>

#include "Graphics/Buffer/ConstantBuffer.h"

using namespace DirectX;

struct alignas(16) CameraBufferData
{
    XMFLOAT3 position;
    float padding; // 16-byte alignment
};

using CameraBuffer = ConstantBuffer<CameraBufferData>;
