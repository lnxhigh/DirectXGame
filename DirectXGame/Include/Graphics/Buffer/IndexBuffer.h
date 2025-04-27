#pragma once
#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class IndexBuffer
{
private:
	ComPtr<ID3D11Buffer> m_buffer = nullptr;
	UINT m_index_count = 0;

public:
	IndexBuffer() = default;
	bool Create(ID3D11Device* device, void* indices, UINT size_list);

	ID3D11Buffer* Get() const { return m_buffer.Get(); }
	ID3D11Buffer** GetAddressOf() { return m_buffer.GetAddressOf(); }
	int GetIndexCount() { return m_index_count; }
};
