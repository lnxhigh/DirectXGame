#include "Resource/Loader/TextureLoader.h"

#include <filesystem>
#include <string>

#include "External/DirectXTex.h"
#include "Resource/Texture.h"

std::shared_ptr<Texture> TextureLoader::Load(const TextureDescriptor& descriptor, ID3D11Device* device)
{
    DirectX::ScratchImage scratch;
    DirectX::TexMetadata metadata;
    std::wstring filename(descriptor.path.begin(), descriptor.path.end());

    // Load file

    HRESULT hr = DirectX::LoadFromWICFile(
        filename.c_str(),
        DirectX::WIC_FLAGS_NONE,
        &metadata,
        scratch
    );

    if (FAILED(hr))
    {
        throw std::runtime_error("Error: Failed to load image " + descriptor.path);
        return nullptr;
    }

    // Convert BGRA to RGBA

    DirectX::ScratchImage converted;

    hr = DirectX::Convert(
        *scratch.GetImage(0, 0, 0),
        DXGI_FORMAT_R8G8B8A8_UNORM,
        DirectX::TEX_FILTER_DEFAULT,
        DirectX::TEX_THRESHOLD_DEFAULT,
        converted
    );

    if (FAILED(hr))
    {
        throw std::runtime_error("Error: Failed to convert BGRA image to RGBA image " + descriptor.path);
        return nullptr;
    }

    // Initialize texture

    const DirectX::Image* img = converted.GetImage(0, 0, 0);
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    texture->Init(device, *img);

    return texture;
}

bool TextureLoader::Supports(const TextureDescriptor& descriptor) const
{
    if (descriptor.type != "texture")
        return false;

    const std::string& path = descriptor.path;
    std::string ext = std::filesystem::path(path).extension().string();
    return ext == ".png";
}
