#pragma once
class VertexBuffer
{
private:
	UINT m_size_vertex;
	UINT m_size_list;
public:
	bool Load(void* vertices, unsigned int size_vertex, unsigned int size_list);

};

