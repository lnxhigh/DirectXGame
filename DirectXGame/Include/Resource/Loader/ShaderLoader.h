#pragma once
#include <memory>

#include "Resource/Loader/IResourceLoader.h"
#include "Resource/Shader.h"

class ShaderLoader : public IResourceLoader<Shader, ShaderDescriptor>
{
public:
    std::shared_ptr<Shader> Load(const ShaderDescriptor& descriptor, ID3D11Device* device) override;
    bool Supports(const ShaderDescriptor& descriptor) const override;
};
