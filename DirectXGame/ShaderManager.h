#pragma once

#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class ShaderManager
{
private:
	ComPtr<ID3D11Device> m_device = nullptr;

	ComPtr<ID3DBlob> m_vs_blob = nullptr;
	ComPtr<ID3D11VertexShader> m_vertex_shader = nullptr;

	ComPtr<ID3DBlob> m_ps_blob = nullptr;
	ComPtr<ID3D11PixelShader> m_pixel_shader = nullptr;

public:
	bool Init(ID3D11Device* device);
	bool LoadVertexShader(const wchar_t* filename);
	bool LoadPixelShader(const wchar_t* filename);

	ID3D11VertexShader* GetVertexShader() const { return m_vertex_shader.Get(); }
	ID3DBlob* GetVertexShaderBlob() const { return m_vs_blob.Get(); }

	ID3D11PixelShader* GetPixelShader() const { return m_pixel_shader.Get(); }
	ID3DBlob* GetPixelShaderBlob() const { return m_ps_blob.Get(); }

};

