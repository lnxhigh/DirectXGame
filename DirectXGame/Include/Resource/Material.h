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
    std::string mtl_path;
    std::string vs_path;
    std::string ps_path;
};

struct MaterialData
{
    XMFLOAT4 diffuse;
    XMFLOAT4 specular;
    float shininess;
};

class Material
{
private:
    MaterialBuffer m_material_buffer;

public:
    std::shared_ptr<Shader> shader = std::make_shared<Shader>();
    std::shared_ptr<Texture> diffuse_map = std::make_shared<Texture>();

private:
    // Material properties
    MaterialData m_material_data;

public:
    const XMFLOAT4 GetDiffuse() const { return m_material_data.diffuse; }
    const XMFLOAT4 GetSpecular() const { return m_material_data.specular; }
    const float GetShininess() const { return m_material_data.shininess; }

    void SetDiffuse(XMFLOAT4 diffuse) { m_material_data.diffuse = diffuse; }
    void SetSpecular(XMFLOAT4 specular) { m_material_data.specular = specular; }
    void SetShininess(float shininess) { m_material_data.shininess = shininess; }

public:
    bool Init(ID3D11Device* device);
    void Update(ID3D11DeviceContext* context);
    void Bind(ID3D11DeviceContext* context);
};
