#pragma once
#include <memory>

#include <d3d11.h>
#include <wrl/client.h>

#include "Resource/Loader/IResourceLoader.h"
#include "Resource/Texture.h"

class TextureLoader : public IResourceLoader<Texture, TextureDescriptor>
{
public:
    std::shared_ptr<Texture> Load(const TextureDescriptor& descriptor, ID3D11Device* device) override;
    bool Supports(const TextureDescriptor& descriptor) const override;
};
