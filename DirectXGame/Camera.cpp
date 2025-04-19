#include "Camera.h"
#include "InputSystem.h"
#include "DirectXMath.h"

#include "windows.h"

using namespace DirectX;

Camera::Camera()
	: m_input_system(nullptr)
{
	// Set initial transform

	m_eye = XMVectorSet(0.0f, 0.0f, -1.0f, 1.0f);
	m_at = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	m_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f); // w = 0

	m_forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f); // w = 0
	m_right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f); // w = 0
}

Camera::~Camera()
{

}

bool Camera::Init(InputSystem* input_system)
{
	m_input_system = input_system;
	input_system->RegisterListener(this);

	return true;
}

void Camera::Move(float dt)
{
	XMVECTOR movement = XMVectorZero();
	XMVECTOR forward = m_forward * XMVectorSet(1.0f, 0.0f, 1.0f, 1.0f);

	if (XMVectorGetX(XMVector3LengthSq(forward)) < 0.01f)
		return;
	else
		forward = XMVector3Normalize(forward);

	XMVECTOR right = XMVector3Normalize(XMVector3Cross(m_up, forward));

	if (m_input_system->GetKeyboard().IsKeyActive('W'))
		movement += forward;

	if (m_input_system->GetKeyboard().IsKeyActive('S'))
		movement -= forward;
		
	if (m_input_system->GetKeyboard().IsKeyActive('D'))
		movement += right;

	if (m_input_system->GetKeyboard().IsKeyActive('A'))
		movement -= right;

	// Apply movement

	if (XMVectorGetX(XMVector3LengthSq(movement)) < 0.01f)
		return;

	movement = XMVector3Normalize(movement);
	movement = XMVectorScale(movement, m_move_speed * dt);

	m_eye += movement;
	m_at += movement;
}

void Camera::OnMouseMove(int dx, int dy)
{
	m_yaw += dx * m_sensitivity;
	m_pitch += -dy * m_sensitivity;

	// Limit pitch

	if (m_pitch >= XM_PIDIV2)
		m_pitch = XM_PIDIV2;
	else if (m_pitch <= -XM_PIDIV2)
		m_pitch = -XM_PIDIV2;

	// Obtain forward and right vector

	float x = cosf(m_pitch) * sinf(m_yaw);
	float y = sinf(m_pitch);
	float z = cosf(m_pitch) * cosf(m_yaw);

	XMVECTOR forward = XMVectorSet(x, y, z, 0.0f);
	m_forward = XMVector3Normalize(forward);
	m_right = XMVector3Normalize(XMVector3Cross(m_up, m_forward));

	// Apply rotation

	m_at = m_eye + m_forward;
}

void Camera::SetTransform(XMFLOAT4 eye, XMFLOAT4 at, XMFLOAT4 up)
{
	m_eye = XMLoadFloat4(&eye);
	m_at = XMLoadFloat4(&at);
	m_up = XMLoadFloat4(&up);
}

void Camera::SetPerspective(float fov, float aspect, float near_z, float far_z)
{
	m_fov = fov;
	m_aspect = aspect;
	m_near = near_z;
	m_far = far_z;
}

void Camera::Update(float dt)
{
	Move(dt);
}
