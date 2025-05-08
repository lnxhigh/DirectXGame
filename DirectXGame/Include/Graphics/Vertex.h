#pragma once
#include <tuple>

#include <DirectXMath.h>

using namespace DirectX;

struct Vertex
{
    XMFLOAT3 position;
    XMFLOAT3 normal;
    XMFLOAT4 color;

    bool operator<(const Vertex& other) const 
    {
        auto first = std::tie(position.x, position.y, position.z, normal.x, normal.y, normal.z);
        auto second = std::tie(other.position.x, other.position.y, other.position.z, other.normal.x, other.normal.y, other.normal.z);
        return first < second;
    }

    bool operator==(const Vertex& other) const 
    {
        return memcmp(this, &other, sizeof(Vertex)) == 0;
    }
};
