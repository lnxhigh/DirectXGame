#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Transform
{
private:
    XMFLOAT3 m_position;
    XMFLOAT3 m_rotation;
    XMFLOAT3 m_scale;

public:
    Transform()
        : m_position(0.0f, 0.0f, 0.0f),
        m_rotation(0.0f, 0.0f, 0.0f),
        m_scale(1.0f, 1.0f, 1.0f) {}

    Transform(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale)
        : m_position(position), m_rotation(rotation), m_scale(scale) {}

    XMMATRIX GetWorldMatrix() const 
    {
        XMMATRIX translation = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
        XMMATRIX rotation = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
        XMMATRIX scale = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
        
        return scale * rotation * translation;
    }

    void SetTransform(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale)
    {
        m_position = position;
        m_rotation = rotation;
        m_scale = scale;
    }
};
