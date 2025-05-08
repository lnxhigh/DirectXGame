#pragma once
#include <string>

#include <d3d11.h>
#include <DirectXMath.h>

#include "Graphics/Buffer/MaterialBuffer.h"
#include "Graphics/Shader/InputLayout.h"
#include "Graphics/Shader/PixelShader.h"
#include "Graphics/Shader/VertexShader.h"
#include "Resource/ResourceDescriptor.h"

using namespace DirectX;

struct MaterialDescriptor : public ResourceDescriptor
{
    std::string mtl_path;
    std::string vs_path;
    std::string ps_path;
};

class Material
{
private:
    VertexShader m_vertex_shader;
    PixelShader m_pixel_shader;
    InputLayout m_input_layout;
    MaterialBuffer m_material_buffer;

private:
    // Material properties

    XMFLOAT4 m_diffuse = XMFLOAT4(1, 1, 1, 1);
    XMFLOAT4 m_specular = XMFLOAT4(1, 1, 1, 1);
    float m_shininess = 1.0f;

public:
    const XMFLOAT4 GetDiffuse() const { return m_diffuse; }
    const XMFLOAT4 GetSpecular() const { return m_specular; }
    const float GetShininess() const { return m_shininess; }

    void SetDiffuse(XMFLOAT4 diffuse) { m_diffuse = diffuse; }
    void SetSpecular(XMFLOAT4 specular) { m_specular = specular; }
    void SetShininess(float shininess) { m_shininess = shininess; }

public:
    bool Init(ID3D11Device* device, const wchar_t* vs_path, const wchar_t* ps_path);
    void Update(ID3D11DeviceContext* context);
    void Bind(ID3D11DeviceContext* context);
};
