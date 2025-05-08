#pragma once
#include <filesystem>
#include "Resource/Loader/IResourceLoader.h"
#include "Resource/Mesh.h"

class MeshLoader : public IResourceLoader<Mesh, MeshDescriptor>
{
public:
    std::shared_ptr<Mesh> Load(const MeshDescriptor& descriptor, ID3D11Device* device) override;
    bool Supports(const MeshDescriptor& descriptor) const override;
};
