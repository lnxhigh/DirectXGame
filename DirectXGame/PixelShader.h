#pragma once
#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class PixelShader
{
private:
	ComPtr<ID3DBlob> m_ps_blob = nullptr;
	ComPtr<ID3D11PixelShader> m_pixel_shader = nullptr;

public:
	PixelShader() = default;
	bool Compile(const wchar_t* filename);
	bool Create(ID3D11Device* device);

	ID3D11PixelShader* Get() const { return m_pixel_shader.Get(); }
	ID3DBlob* GetShaderBlob() const { return m_ps_blob.Get(); }
};

