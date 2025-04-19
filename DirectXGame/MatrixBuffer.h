#pragma once
#include <DirectXMath.h>

#include "ConstantBuffer.h"

using namespace DirectX;

struct alignas(16) MatrixBufferData
{
    XMFLOAT4X4 world;
    XMFLOAT4X4 view;
    XMFLOAT4X4 proj;
    XMFLOAT4X4 world_inv_transpose;
};

using MatrixBuffer = ConstantBuffer<MatrixBufferData>;
