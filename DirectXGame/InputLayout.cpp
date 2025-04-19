#include "InputLayout.h"
#include "Vertex.h"

bool InputLayout::Create(ID3D11Device* device, void* shader_byte_code, SIZE_T size_byte_code)
{
    // Create the vertex input layout
    // SemanticName - SemanticIndex - Format - InputSlot -  AlignedByteOffset - 
    // InputSlotClass - InstanceDataStepRate

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, normal), D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, color), D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    ComPtr<ID3D11InputLayout> input_layout = nullptr;
    HRESULT hr = device->CreateInputLayout(
        layout, ARRAYSIZE(layout),
        shader_byte_code, size_byte_code, 
        input_layout.GetAddressOf()
    );

    if (FAILED(hr))
    {
        OutputDebugStringA("Error: Failed to create an input layout\n");
        return false;
    }

    // Assign input layout

    m_input_layout = input_layout;

    return true;
}
