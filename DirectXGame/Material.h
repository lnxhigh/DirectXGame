#pragma once
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
    VertexShader& GetVertexShader() { return m_vertex_shader; }
    PixelShader& GetPixelShader() { return m_pixel_shader; }
    InputLayout& GetInputLayout() { return m_input_layout; }
};
