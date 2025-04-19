#pragma once
#include <d3d11.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Mesh
{
private:
	VertexBuffer m_vertex_buffer;
	IndexBuffer m_index_buffer;

public:
	void Bind(ID3D11DeviceContext* context)
	{
		UINT stride = m_vertex_buffer.GetStride();
		UINT offset = m_vertex_buffer.GetOffset();

		context->IASetVertexBuffers(0, 1, m_vertex_buffer.GetAddressOf(), &stride, &offset);
		context->IASetIndexBuffer(m_index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

public:
	VertexBuffer& GetVertexBuffer() { return m_vertex_buffer; }
	IndexBuffer& GetIndexBuffer() { return m_index_buffer; }
};
