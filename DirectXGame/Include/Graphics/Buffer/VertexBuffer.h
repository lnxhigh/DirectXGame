#pragma once
#include <d3d11.h>
#include <wrl/client.h>

#include "Graphics/Vertex.h"

using Microsoft::WRL::ComPtr;

class VertexBuffer
{
private:
	ComPtr<ID3D11Buffer> m_buffer = nullptr;
	UINT m_stride = sizeof(Vertex);
	UINT m_offset = 0;

public:
	VertexBuffer() = default;
	bool Create(ID3D11Device* device, void* vertices, UINT size_vertex, UINT size_list);

	ID3D11Buffer* Get() { return m_buffer.Get(); }
	ID3D11Buffer** GetAddressOf() { return m_buffer.GetAddressOf(); }
	UINT GetStride() const { return m_stride; }
	UINT GetOffset() const { return m_offset; }
};
