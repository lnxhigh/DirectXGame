#pragma once
#include <memory>
#include <vector>

#include <d3d11.h>

#include "Component/Component.h"
#include "Component/MaterialComponent.h"
#include "Component/MeshComponent.h"
#include "Component/TransformComponent.h"
#include "Entity/Entity.h"

#include "Scene/Camera.h"
#include "Scene/Light.h"

class Window;
class InputSystem;

class Scene
{
private:
	std::vector<std::shared_ptr<Entity>> m_entities;
	Camera m_camera;
	Light m_light;

public:
	bool Init(Window* window, ID3D11Device* device, InputSystem* input_system);
	void Update(float dt);
	void Update(ID3D11DeviceContext* context);

public:
	void AddEntity(std::shared_ptr<Entity> entity) { m_entities.push_back(std::move(entity)); }

public:
	std::vector<std::shared_ptr<Entity>>& GetEntities() { return m_entities; }
	Camera& GetCamera() { return m_camera; }
	Light& GetLight() { return m_light; }

};
