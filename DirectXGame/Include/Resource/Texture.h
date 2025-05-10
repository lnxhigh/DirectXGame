#pragma once
#include <d3d11.h>
#include <wrl/client.h>

#include "External/DirectXTex.h"
#include "Resource/ResourceDescriptor.h"

using Microsoft::WRL::ComPtr;

struct TextureDescriptor : ResourceDescriptor
{
    std::string path;
};

class Texture 
{
private:
    ComPtr<ID3D11Texture2D> m_texture = nullptr;
    ComPtr<ID3D11ShaderResourceView> m_srv = nullptr;

public:
    bool Texture::Init(ID3D11Device* device, const DirectX::Image& image);
    void Bind(ID3D11DeviceContext* context, UINT slot = 0);

    ID3D11ShaderResourceView* GetSRV() const { return m_srv.Get(); }
};
