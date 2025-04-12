#include "VertexShader.h"
#include <d3dcompiler.h>

bool VertexShader::Compile(const wchar_t* filename)
{
    ComPtr<ID3DBlob> vs_blob = nullptr;
    ComPtr<ID3DBlob> err_blob = nullptr;

    // Compile Vertex Shader

    HRESULT hr = D3DCompileFromFile(
        filename,
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main", "vs_5_0",
        0, 0,
        vs_blob.GetAddressOf(), err_blob.GetAddressOf()
    );

    if (FAILED(hr)) 
    {
        OutputDebugStringA("Error: Failed to compile a vertex shader from the file.\n");
        if (err_blob)
            OutputDebugStringA((char*)err_blob->GetBufferPointer());

        return false;
    }

    // Assign blob

    m_vs_blob = vs_blob;

    return true;
}

bool VertexShader::Create(ID3D11Device* device)
{
    ComPtr<ID3D11VertexShader> vertex_shader = nullptr;

    // Create Vertex Shader

    HRESULT hr = device->CreateVertexShader(
        m_vs_blob->GetBufferPointer(),
        m_vs_blob->GetBufferSize(),
        nullptr,
        vertex_shader.GetAddressOf()
    );

    if (FAILED(hr))
    {
        OutputDebugStringA("Error: Failed to create a vertex shader.\n");
        return false;
    }

    // Assign vertex shader

    m_vertex_shader = vertex_shader;

    return true;
}
