#pragma once
#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class Sampler
{
private:
	ComPtr<ID3D11SamplerState> m_sampler;
public:
	bool Init(ID3D11Device* device);
	void Bind(ID3D11DeviceContext* context);
};
