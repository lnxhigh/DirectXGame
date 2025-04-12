#pragma once

#include "InputListener.h"
#include "DirectXMath.h"

class InputSystem;

using namespace DirectX;

class Camera : public InputListener
{
private:
    // Input system

    InputSystem* m_input_system = nullptr;

    // Transform

    XMVECTOR m_eye = XMVectorSet(0.0f, 0.0f, -1.0f, 1.0f);
    XMVECTOR m_at = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
    XMVECTOR m_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f); // w = 0

    XMVECTOR m_forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f); // w = 0
    XMVECTOR m_right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f); // w = 0

    // Projection

    float m_fov = XMConvertToRadians(45.0f);
    float m_aspect = 1.0f;
    float m_near = 0.1f;
    float m_far = 100.0f;

    // Rotation

    float m_yaw = 0.0f;
    float m_pitch = 0.0f;
    
    // Speed parameters

    float m_move_speed = 1.5f;
    float m_sensitivity = 0.002f;

public:
    Camera();
    ~Camera();

public:
    bool Init(InputSystem* input_system);
    void Move(float dt);
    void OnMouseMove(int dx, int dy);
    
    void SetTransform(XMVECTOR eye, XMVECTOR at, XMVECTOR up);
    void SetPerspective(float fov, float aspect, float near_z, float far_z);

    XMMATRIX GetViewMatrix() const { return XMMatrixLookAtLH(m_eye, m_at, m_up); }
    XMMATRIX GetProjectionMatrix() const { return XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_near, m_far); }

    void Update(float dt);
};
