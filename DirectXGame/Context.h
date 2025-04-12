#pragma once
#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class Viewport;
class MatrixBuffer;
class Mesh;
class Material;

class Context
{
private:
	ComPtr<ID3D11DeviceContext> m_context;

public:
	bool Init(ID3D11DeviceContext* context);
	ID3D11DeviceContext* Get() { return m_context.Get(); }

public:
	void Bind(const Viewport& viewport);
	void Bind(MatrixBuffer& matrix_buffer);
	void Bind(Mesh& mesh);
	void Bind(Material& material);
};
