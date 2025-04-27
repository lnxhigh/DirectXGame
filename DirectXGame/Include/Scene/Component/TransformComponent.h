#pragma once
#include <DirectXMath.h>

#include "Scene/Component/Component.h"

using namespace DirectX;

class TransformComponent : public Component
{
public:
    XMFLOAT3 position = XMFLOAT3(0.0f, 0.0f, 0.0f);
    XMFLOAT3 rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
    XMFLOAT3 scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

public:
    TransformComponent() = default;

    XMMATRIX GetWorldMatrix() const
    {
        XMMATRIX translation_matrix = XMMatrixTranslation(position.x, position.y, position.z);
        XMMATRIX rotation_matrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
        XMMATRIX scale_matrix = XMMatrixScaling(scale.x, scale.y, scale.z);

        return scale_matrix * rotation_matrix * translation_matrix;
    }
};
