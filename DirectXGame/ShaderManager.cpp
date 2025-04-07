#include "ShaderManager.h"
#include <d3dcompiler.h>

bool ShaderManager::Init(ID3D11Device* device)
{
    m_device = device;

    return true;
}

bool ShaderManager::LoadVertexShader(const wchar_t* filename)
{
    ComPtr<ID3DBlob> vs_blob = nullptr;
    ComPtr<ID3DBlob> err_blob = nullptr;
    ComPtr<ID3D11VertexShader> vertex_shader = nullptr;
    
    // Compile Vertex Shader

    HRESULT hr = D3DCompileFromFile(
        filename,
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main", "vs_5_0",
        0, 0,
        vs_blob.GetAddressOf(), err_blob.GetAddressOf()
    );

    if (FAILED(hr)) {
        if (err_blob)
        {
            OutputDebugStringA("Error: Failed to compile a vertex shader from the file.\n");
            OutputDebugStringA((char*)err_blob->GetBufferPointer());
        }
        return false;
    }

    // Create Vertex Shader

    hr = m_device->CreateVertexShader(
        vs_blob->GetBufferPointer(),
        vs_blob->GetBufferSize(),
        nullptr,
        vertex_shader.GetAddressOf()
    );

    if (FAILED(hr))
    {
        OutputDebugStringA("Error: Failed to create a vertex shader.\n");
        return false;
    }

    m_vs_blob = vs_blob;
    m_vertex_shader = vertex_shader;

    return true;
}

bool ShaderManager::LoadPixelShader(const wchar_t* filename)
{
    ComPtr<ID3DBlob> ps_blob = nullptr;
    ComPtr<ID3DBlob> err_blob = nullptr;
    ComPtr<ID3D11PixelShader> pixel_shader = nullptr;

    // Compile Pixel Shader

    HRESULT hr = D3DCompileFromFile(
        filename,
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main", "ps_5_0",
        0, 0,
        ps_blob.GetAddressOf(), err_blob.GetAddressOf()
    );

    if (FAILED(hr)) {
        if (err_blob)
        {
            OutputDebugStringA("Error: Failed to compile a pixel shader from the file.\n");
            OutputDebugStringA((char*)err_blob->GetBufferPointer());
        }
        return false;
    }

    // Create Pixel Shader

    hr = m_device->CreatePixelShader(
        ps_blob->GetBufferPointer(),
        ps_blob->GetBufferSize(),
        nullptr,
        pixel_shader.GetAddressOf()
    );

    if (FAILED(hr))
    {
        OutputDebugStringA("Error: Failed to create a pixel shader.\n");
        return false;
    }

    m_ps_blob = ps_blob;
    m_pixel_shader = pixel_shader;

    return true;
}
