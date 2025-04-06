#include "VertexBuffer.h"
#include <d3d11.h>

bool VertexBuffer::Load(void* vertices, unsigned int size_vertex, unsigned int size_list)
{
	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = size_vertex * size_list;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	m_size_vertex = size_vertex;
	m_size_list = size_list;

	D3D11_SUBRESOURCE_DATA init_data = { };
	init_data.pSysMem = vertices;

	return true;

}
