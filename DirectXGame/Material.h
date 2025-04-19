#pragma once
#include <d3d11.h>

#include "VertexShader.h"
#include "PixelShader.h"
#include "InputLayout.h"

class Material
{
private:
    VertexShader m_vertex_shader;
    PixelShader m_pixel_shader;
    InputLayout m_input_layout;

public:
    void Bind(ID3D11DeviceContext* context)
    {
        context->IASetInputLayout(m_input_layout.Get());
        context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
        context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
    }

public:
    VertexShader& GetVertexShader() { return m_vertex_shader; }
    PixelShader& GetPixelShader() { return m_pixel_shader; }
    InputLayout& GetInputLayout() { return m_input_layout; }
};
