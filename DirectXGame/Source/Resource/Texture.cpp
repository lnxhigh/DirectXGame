#include "Resource/Texture.h"

bool Texture::Init(ID3D11Device* device, const DirectX::Image& image)
{
    // Texture

    D3D11_TEXTURE2D_DESC tex_desc = {};

    tex_desc.Width = (UINT)image.width;
    tex_desc.Height = (UINT)image.height;
    tex_desc.MipLevels = 1;
    tex_desc.ArraySize = 1;
    tex_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    tex_desc.SampleDesc.Count = 1;
    tex_desc.Usage = D3D11_USAGE_IMMUTABLE;
    tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA init_data = {};
    init_data.pSysMem = image.pixels;
    init_data.SysMemPitch = (UINT)image.rowPitch;

    ComPtr<ID3D11Texture2D> texture;
    HRESULT hr = device->CreateTexture2D(&tex_desc, &init_data, &texture);

    if (FAILED(hr))
    {
        OutputDebugStringA("Error: Failed to create texture\n");
        return false;
    }

    // Shader Resource View

    D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};

    srv_desc.Format = tex_desc.Format;
    srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srv_desc.Texture2D.MostDetailedMip = 0;
    srv_desc.Texture2D.MipLevels = 1;

    ComPtr<ID3D11ShaderResourceView> srv;
    hr = device->CreateShaderResourceView(texture.Get(), &srv_desc, srv.GetAddressOf());

    if (FAILED(hr))
    {
        OutputDebugStringA("Error: Failed to create ShaderResourceView\n");
        return false;
    }

    // Now assign values

    m_texture = texture;
    m_srv = srv;

    return true;
}

void Texture::Bind(ID3D11DeviceContext* context, UINT slot)
{
    context->PSSetShaderResources(slot, 1, m_srv.GetAddressOf());
}
