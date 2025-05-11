#include "Window/Window.h"
#include "Scene/Scene.h"

bool Scene::Init(Window* window, ID3D11Device* device, InputSystem* input_system)
{
    // Light

    m_light.Init(device);
    
    m_light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    m_light.specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    m_light.ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);

    m_light.direction = XMFLOAT3(-1.0f, -1.0f, 0.0f);

    // Camera

    XMFLOAT4 eye = XMFLOAT4(30.0f, 3.0f, 20.0f, 1.0f);
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

void Scene::Update(ID3D11DeviceContext* context)
{
    m_camera.Update(context);
    m_light.Update(context);
}
