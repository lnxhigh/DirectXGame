#pragma once
#include <vector>
#include <DirectXMath.h>

#include "Vertex.h"

using namespace DirectX;

class Icosahedron
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

private:
    float t = 1.61803398875f;

    XMFLOAT3 m_position[12] =
    {
        {-1,  t,  0}, { 1,  t,  0}, {-1, -t,  0}, { 1, -t,  0},
        { 0, -1,  t}, { 0,  1,  t}, { 0, -1, -t}, { 0,  1, -t},
        { t,  0, -1}, { t,  0,  1}, {-t,  0, -1}, {-t,  0,  1}
    };

public:
    Icosahedron(float radius = 1.0f, XMFLOAT4 color = XMFLOAT4(0, 0, 0, 1))
    {
        Generate(radius, color);
    }

    void Generate(float radius, XMFLOAT4 color)
    {
        // Vertex
        
        //// Initialize
        
        vertices.clear();
        int num_vertices = ARRAYSIZE(m_position);
        vertices.resize(num_vertices);

        //// Generate

        for (int i = 0; i < num_vertices; ++i)
        {
            Vertex& vertex = vertices[i];
            XMVECTOR vec = XMLoadFloat3(&m_position[i]);
            vec = XMVectorScale(vec, radius);
            
            XMFLOAT3 position;
            XMStoreFloat3(&position, vec);

            XMFLOAT3 normal;
            XMStoreFloat3(&normal, XMVector3Normalize(vec));

            vertex.position = position;
            vertex.normal = normal;
            vertex.color = color;
        }

        // Index

        //// Initialize

        indices.clear();

        //// Generate

        indices = 
        {
            0, 11, 5, 0, 5, 1, 0, 1, 7, 0, 7, 10,
            0, 10, 11, 1, 5, 9, 5, 11, 4, 11, 10, 2,
            10, 7, 6, 7, 1, 8, 3, 9, 4, 3, 4, 2,
            3, 2, 6, 3, 6, 8, 3, 8, 9, 4, 9, 5,
            2, 4, 11, 6, 2, 10, 8, 6, 7, 9, 8, 1
        };
    }

};
