#include "Resource/Loader/MeshLoader.h"

#include <map>
#include <string>
#include <vector>

#include "External/tiny_obj_loader.h"

std::shared_ptr<Mesh> MeshLoader::Load(const MeshDescriptor& descriptor, ID3D11Device* device) 
{
    // Read from file

    tinyobj::ObjReader reader;
    tinyobj::ObjReaderConfig config;

    if (!reader.ParseFromFile(descriptor.path, config)) {
        OutputDebugStringA(reader.Error().c_str());
        return nullptr;
    }

    if (!reader.Warning().empty()) {
        OutputDebugStringA(reader.Warning().c_str());
    }

    // Process

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::map<Vertex, uint32_t> map_vertices;

    const auto& attrib = reader.GetAttrib();
    const auto& shapes = reader.GetShapes();

    for (const auto& shape : shapes)
    {
        size_t index_offset = 0;

        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
        {
            for (size_t v = 0; v < shape.mesh.num_face_vertices[f]; v++)
            {
                const auto& idx = shape.mesh.indices[index_offset + v];

                Vertex vertex = {};

                if (idx.vertex_index >= 0) 
                {
                    vertex.position.x = attrib.vertices[3 * idx.vertex_index + 0];
                    vertex.position.y = attrib.vertices[3 * idx.vertex_index + 1];
                    vertex.position.z = attrib.vertices[3 * idx.vertex_index + 2];
                }

                if (idx.normal_index >= 0) 
                {
                    vertex.normal.x = attrib.normals[3 * idx.normal_index + 0];
                    vertex.normal.y = attrib.normals[3 * idx.normal_index + 1];
                    vertex.normal.z = attrib.normals[3 * idx.normal_index + 2];
                }

                if (idx.texcoord_index >= 0) 
                {
                    // vertex.texcoord.x = attrib.texcoords[2 * idx.texcoord_index + 0];
                    // vertex.texcoord.y = 1.0f - attrib.texcoords[2 * idx.texcoord_index + 1]; // flip V
                }

                if (map_vertices.count(vertex) == 0) {
                    map_vertices[vertex] = static_cast<uint32_t>(vertices.size());
                    vertices.push_back(vertex);
                }

                indices.push_back(map_vertices[vertex]);
            }

            index_offset += shape.mesh.num_face_vertices[f];
        }
    }

    // Initialize mesh

    auto mesh = std::make_shared<Mesh>();

    bool flag = mesh->Init(
        device,
        vertices.data(), sizeof(Vertex), static_cast<UINT>(vertices.size()),
        indices.data(), static_cast<UINT>(indices.size())
    );

    if (!flag)
    {
        OutputDebugStringA("Error: Mesh loader failed to load mesh\n");
        return nullptr;
    }

    return mesh;
}

bool MeshLoader::Supports(const MeshDescriptor& descriptor) const
{
    if (descriptor.type != "mesh")
        return false;

    const std::string& path = descriptor.path;
    std::string ext = std::filesystem::path(path).extension().string();
    return ext == ".obj";
}
