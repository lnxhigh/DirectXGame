#pragma once
#include <string>

#include <d3d11.h>

#include "Graphics/Buffer/IndexBuffer.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Resource/ResourceDescriptor.h"

struct MeshDescriptor : ResourceDescriptor
{

};

class Mesh
{
private:
	VertexBuffer m_vertex_buffer;
	IndexBuffer m_index_buffer;

public:
	bool Init(
		ID3D11Device* device,
		void* vertices, UINT size_vertex, UINT size_vertices_list,
		void* indices, UINT size_indices_list
	);

	void Bind(ID3D11DeviceContext* context);

public:
	VertexBuffer& GetVertexBuffer() { return m_vertex_buffer; }
	IndexBuffer& GetIndexBuffer() { return m_index_buffer; }
};
