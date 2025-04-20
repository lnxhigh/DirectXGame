#include "Mesh.h"

bool Mesh::Init(
	ID3D11Device* device,
	void* vertices, UINT size_vertex, UINT size_vertices_list, 
	void* indices, UINT size_indices_list)
{
	// Vertex Buffer

	if (!m_vertex_buffer.Create(device, vertices, size_vertex, size_vertices_list))
		return false;

	// Index Buffer

	if (!m_index_buffer.Create(device, indices, size_indices_list))
		return false;

	// Now success

	return true;
}

void Mesh::Bind(ID3D11DeviceContext* context)
{
	UINT stride = m_vertex_buffer.GetStride();
	UINT offset = m_vertex_buffer.GetOffset();

	context->IASetVertexBuffers(0, 1, m_vertex_buffer.GetAddressOf(), &stride, &offset);
	context->IASetIndexBuffer(m_index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}