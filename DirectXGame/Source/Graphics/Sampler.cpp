#include "Graphics/Sampler.h"

bool Sampler::Init(ID3D11Device* device)
{
	D3D11_SAMPLER_DESC desc = {};
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	HRESULT hr = device->CreateSamplerState(&desc, &m_sampler);

	if (FAILED(hr))
	{
		OutputDebugStringA("Error: Failed to create SamplerState\n");
		return false;
	}

	return true;
}

void Sampler::Bind(ID3D11DeviceContext* context)
{
	context->PSSetSamplers(0, 1, m_sampler.GetAddressOf());
}
