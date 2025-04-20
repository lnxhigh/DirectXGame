#include "Light.h"

bool Light::Init(ID3D11Device* device)
{
	// Light Buffer

	if (!m_light_buffer.Create(device))
		return false;

	// Now success

	return true;
}

void Light::Update(ID3D11DeviceContext* context)
{
	auto& light_data = m_light_buffer.Data();

	light_data.color = m_color;
	light_data.direction = m_direction;
	light_data.ambient = m_ambient;

	m_light_buffer.Update(context);
}

void Light::Bind(ID3D11DeviceContext* context)
{
	m_light_buffer.Bind(context, ShaderStage::Pixel, 1); // b1 in pixel shader
}
