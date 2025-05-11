#pragma once
#include <memory>
#include <string>

#include <d3d11.h>
#include <DirectXMath.h>

#include "Graphics/Buffer/MaterialBuffer.h"
#include "Graphics/Shader/InputLayout.h"
#include "Graphics/Shader/PixelShader.h"
#include "Graphics/Shader/VertexShader.h"
#include "Resource/ResourceDescriptor.h"
#include "Resource/Shader.h"
#include "Resource/Texture.h"


using namespace DirectX;

struct MaterialDescriptor : public ResourceDescriptor
{
    
};

struct MaterialData
{
    XMFLOAT4 diffuse;
    XMFLOAT4 specular;
    XMFLOAT4 ambient;
    XMFLOAT4 emissive;

    float shininess;
};

class Material
{
private:
    MaterialBuffer m_material_buffer;

public:
    std::shared_ptr<Shader> shader = std::make_shared<Shader>();
    std::shared_ptr<Texture> diffuse_map = std::make_shared<Texture>();

public:
    // Material properties
    MaterialData material_data;

public:
    bool Init(ID3D11Device* device);
    void Update(ID3D11DeviceContext* context);
    void Bind(ID3D11DeviceContext* context);
};
