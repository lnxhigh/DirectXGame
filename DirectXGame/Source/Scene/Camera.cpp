#include "Scene/Camera.h"

#include <windows.h>
#include <DirectXMath.h>

#include "Input/InputSystem.h"

using namespace DirectX;

Camera::Camera()
	: m_input_system(nullptr)
{
	// Set initial transform

	XMFLOAT4 eye = XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f);
	XMFLOAT4 at = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 up = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);

	SetTransform(eye, at, up);
}

Camera::~Camera()
{

}

bool Camera::Init(ID3D11Device* device, InputSystem* input_system)
{
	// Camera Buffer

	if (!m_camera_buffer.Create(device))
		return false;

	// Input System

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

	m_forward = XMVector3Normalize(m_at - m_eye);
	m_right = XMVector3Normalize(XMVector3Cross(m_up, m_forward));

	m_pitch = asinf(XMVectorGetY(m_forward));
	m_yaw = atan2f(XMVectorGetX(m_forward), XMVectorGetZ(m_forward));
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

void Camera::Update(ID3D11DeviceContext* context)
{
	auto& camera_data = m_camera_buffer.Data();
	XMStoreFloat3(&camera_data.position, m_eye);
	m_camera_buffer.Update(context);
}

void Camera::Bind(ID3D11DeviceContext* context) 
{
	m_camera_buffer.Bind(context, ShaderStage::Pixel, 3); // b3 in pixel shader
}
