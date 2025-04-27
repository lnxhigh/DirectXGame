#pragma once
#include <vector>

#include <DirectXMath.h>

#include "Graphics/Vertex.h"

using namespace DirectX;

class Cube
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Cube(float size = 1.0, XMFLOAT4 color = XMFLOAT4(0, 0, 0, 1)) 
	{
		Generate(size, color);
	};

private:
    XMFLOAT3 m_position[8] =
    {
        {-1, -1, -1}, {-1, +1, -1}, {+1, +1, -1}, {+1, -1, -1},
        {-1, -1, +1}, {-1, +1, +1}, {+1, +1, +1}, {+1, -1, +1}
    };

private:
    void Generate(float size, XMFLOAT4 color)
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
            vec = XMVectorScale(vec, size * 0.5f);
            XMFLOAT3 position;
            XMStoreFloat3(&position, vec);
            
            vertex.position = position;
            vertex.color = color;
        }

        // Index

        //// Initialize

        indices.clear();

        //// Generate

        indices =
        {
            // Front face
            0, 1, 2, 0, 2, 3,

            // Back face
            4, 6, 5, 4, 7, 6,

            // Left face
            4, 5, 1, 4, 1, 0,

            // Right face
            3, 2, 6, 3, 6, 7,

            // Top face
            1, 5, 6, 1, 6, 2,

            // Bottom face
            4, 0, 3, 4, 3, 7,
        };

    }
};
