#include "GeometryUtil.h"

void GeometryUtil::ComputeNormals(
	void* vertex_list, unsigned int size_vertex_list, 
	void* index_list, unsigned int size_index_list)
{
    Vertex* vertices = reinterpret_cast<Vertex*>(vertex_list);
    unsigned int* indices = reinterpret_cast<unsigned int*>(index_list);

    // Initialize normal

    for (unsigned int i = 0; i < size_vertex_list; i++)
    {
        vertices[i].normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
    }

    // Traverse all triangles

    for (unsigned int i = 0; i < size_index_list; i += 3)
    {
        unsigned int i0 = indices[i];
        unsigned int i1 = indices[i + 1];
        unsigned int i2 = indices[i + 2];

        const XMFLOAT3& p0 = vertices[i0].position;
        const XMFLOAT3& p1 = vertices[i1].position;
        const XMFLOAT3& p2 = vertices[i2].position;

        XMVECTOR v0 = XMLoadFloat3(&p0);
        XMVECTOR v1 = XMLoadFloat3(&p1);
        XMVECTOR v2 = XMLoadFloat3(&p2);

        XMVECTOR e1 = v1 - v0;
        XMVECTOR e2 = v2 - v0;
        XMVECTOR face_normal = XMVector3Normalize(XMVector3Cross(e1, e2));

        // Accumulate vertex normal

        for (unsigned int idx : { i0, i1, i2 })
        {
            XMVECTOR vertex_normal = XMLoadFloat3(&vertices[idx].normal);
            vertex_normal = XMVectorAdd(vertex_normal, face_normal);
            XMStoreFloat3(&vertices[idx].normal, vertex_normal);
        }
    }

    // Normalize vertex normal

    for (unsigned int i = 0; i < size_vertex_list; i++)
    {
        XMVECTOR vertex_normal = XMLoadFloat3(&vertices[i].normal);
        vertex_normal = XMVector3Normalize(vertex_normal);
        XMStoreFloat3(&vertices[i].normal, vertex_normal);
    }

}
