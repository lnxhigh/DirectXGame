#pragma once

#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class IndexBuffer
{
private:
	ComPtr<ID3D11Device> m_device = nullptr;
	ComPtr<ID3D11Buffer> m_index_buffer = nullptr;

public:
	bool Init(ID3D11Device* device);
	bool Load(void* indices, UINT size_list);

	ID3D11Buffer* GetIndexBuffer() const { return m_index_buffer.Get(); }
	ID3D11Buffer** GetIndexBufferAddress() { return m_index_buffer.GetAddressOf(); }
};
