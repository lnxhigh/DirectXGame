#pragma once

#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class VertexBuffer
{
private:
	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11Buffer> m_vertex_buffer;
	ComPtr<ID3D11InputLayout> m_input_layout;

	bool Load(void* vertices, unsigned int size_vertex, unsigned int size_list,
		void* shader_byte_code, unsigned int size_byte_code);

public:
	VertexBuffer(ID3D11Device *device);
	~VertexBuffer();

	ID3D11Buffer* GetVertexBuffer() const { return m_vertex_buffer.Get(); }
	ID3D11InputLayout* GetInputLayout() const { return m_input_layout.Get(); }
};

