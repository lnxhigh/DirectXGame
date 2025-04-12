#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Mesh 
{
private:
    VertexBuffer m_vertex_buffer;
    IndexBuffer m_index_buffer;

public:
    VertexBuffer& GetVertexBuffer() { return m_vertex_buffer; }
    IndexBuffer& GetIndexBuffer() { return m_index_buffer; }
};
