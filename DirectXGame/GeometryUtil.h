#pragma once
#include <vector>
#include <DirectXMath.h>
#include "Vertex.h"

using namespace DirectX;

class GeometryUtil
{
public:
    static void ComputeNormals(
        void* vertex_list, unsigned int size_vertex_list,
        void* index_list, unsigned int size_index_list);
    
};