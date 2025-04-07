#pragma once

#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class VertexBuffer
{
private:
	ComPtr<ID3D11Device> m_device = nullptr;
	ComPtr<ID3D11Buffer> m_vertex_buffer = nullptr;
	ComPtr<ID3D11InputLayout> m_input_layout = nullptr;

public:
	bool Init(ID3D11Device* device);

	bool Load(void* vertices, UINT size_vertex, UINT size_list,
		void* shader_byte_code, SIZE_T size_byte_code);

	ID3D11Buffer* GetVertexBuffer() const { return m_vertex_buffer.Get(); }
	ID3D11Buffer** GetVertexBufferAddress() { return m_vertex_buffer.GetAddressOf(); }

	ID3D11InputLayout* GetInputLayout() const { return m_input_layout.Get(); }
	ID3D11InputLayout** GetInputLayoutAddress() { return m_input_layout.GetAddressOf(); }
};
