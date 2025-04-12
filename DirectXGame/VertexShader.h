#pragma once
#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class VertexShader
{
private:
	ComPtr<ID3DBlob> m_vs_blob = nullptr;
	ComPtr<ID3D11VertexShader> m_vertex_shader = nullptr;

public:
	VertexShader() = default;
	bool Compile(const wchar_t* filename);
	bool Create(ID3D11Device* device);

	ID3D11VertexShader* Get() const { return m_vertex_shader.Get(); }
	ID3DBlob* GetShaderBlob() const { return m_vs_blob.Get(); }
};

