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
    XMVECTOR m_eye;
    XMVECTOR m_at;
    XMVECTOR m_up;

    XMVECTOR m_forward;
    XMVECTOR m_right;

    // Rotation
    float m_yaw = 0.0f;
    float m_pitch = 0.0f;
    
    // Speed parameters
    float m_move_speed = 1.5f;
    float m_sensitivity = 0.002f;

    // View matrix
    XMMATRIX m_view;

public:
    Camera();
    ~Camera();

public:
    bool Init(InputSystem* input_system);
    void Move(float dt);
    void OnMouseMove(int dx, int dy);
    
    void SetCameraTransform(XMVECTOR eye, XMVECTOR at, XMVECTOR up);
    XMMATRIX GetViewMatrix() const { return m_view; }

    void Update(float dt);
};
