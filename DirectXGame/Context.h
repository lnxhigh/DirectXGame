#pragma once

#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class Context
{
private:
	ComPtr<ID3D11DeviceContext> m_context;

public:
	bool Init(ID3D11DeviceContext* context);
	ID3D11DeviceContext* Get() { return m_context.Get(); }
};

