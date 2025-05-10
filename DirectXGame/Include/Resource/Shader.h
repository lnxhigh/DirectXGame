#pragma once
#include <string>

#include <d3d11.h>

#include "Graphics/Shader/VertexShader.h"
#include "Graphics/Shader/PixelShader.h"
#include "Graphics/Shader/InputLayout.h"
#include "Resource/ResourceDescriptor.h"

struct ShaderDescriptor : ResourceDescriptor
{
    std::string vertex_shader_path;
    std::string pixel_shader_path;
};

class Shader 
{
public:
    bool Init(ID3D11Device* device, const ShaderDescriptor& descriptor);
    void Bind(ID3D11DeviceContext* context);

private:
    VertexShader m_vertex_shader;
    PixelShader m_pixel_shader;
    InputLayout m_input_layout;
};
