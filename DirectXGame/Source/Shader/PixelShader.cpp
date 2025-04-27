#include "Graphics/Shader/PixelShader.h"

#include <d3dcompiler.h>

bool PixelShader::Compile(const wchar_t* filename)
{
    ComPtr<ID3DBlob> ps_blob = nullptr;
    ComPtr<ID3DBlob> err_blob = nullptr;

    // Compile Pixel Shader

    HRESULT hr = D3DCompileFromFile(
        filename,
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main", "ps_5_0",
        0, 0,
        ps_blob.GetAddressOf(), err_blob.GetAddressOf()
    );

    if (FAILED(hr))
    {
        OutputDebugStringA("Error: Failed to compile a pixel shader from the file.\n");
        if (err_blob)
            OutputDebugStringA((char*)err_blob->GetBufferPointer());

        return false;
    }

    // Assign blob

    m_ps_blob = ps_blob;

    return true;
}

bool PixelShader::Create(ID3D11Device* device)
{
    ComPtr<ID3D11PixelShader> pixel_shader = nullptr;

    // Create Vertex Shader

    HRESULT hr = device->CreatePixelShader(
        m_ps_blob->GetBufferPointer(),
        m_ps_blob->GetBufferSize(),
        nullptr,
        pixel_shader.GetAddressOf()
    );

    if (FAILED(hr))
    {
        OutputDebugStringA("Error: Failed to create a pixel shader.\n");
        return false;
    }

    // Assign pixel shader

    m_pixel_shader = pixel_shader;

    return true;
}
