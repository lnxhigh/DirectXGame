#include "Window/Window.h"
#include "Scene/Scene.h"

bool Scene::Init(Window* window, ID3D11Device* device, InputSystem* input_system)
{
    // Light

    m_light.Init(device);
    m_light.SetColor(XMFLOAT4(1, 1, 1, 1));
    m_light.SetDirection(XMFLOAT3(0, -1, +1));
    m_light.SetAmbient(XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f));

    // Camera

    XMFLOAT4 eye = XMFLOAT4(6.0f, 0.0f, -6.0f, 1.0f);
    XMFLOAT4 at = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
    XMFLOAT4 up = XMFLOAT4(0.0f, 1.0f, 0.0f, 0.0f);

    m_camera.Init(device, input_system);
    m_camera.SetTransform(eye, at, up);
    m_camera.SetPerspective(0.75f, window->GetAspectRatio(), 0.1f, 100.0f);

	return true;
}

void Scene::Update(float dt)
{
	m_camera.Update(dt);
}
