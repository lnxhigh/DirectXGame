#include "Context.h"
#include "Viewport.h"
#include "MatrixBuffer.h"
#include "Mesh.h"
#include "Material.h"

bool Context::Init(ID3D11DeviceContext* context)
{
    m_context = context;
    return true;
}

void Context::Bind(const Viewport& viewport)
{
    m_context->RSSetViewports(1, &viewport.Get());
}

void Context::Bind(MatrixBuffer& matrix_buffer)
{
    D3D11_MAPPED_SUBRESOURCE resource;

    if (SUCCEEDED(m_context->Map(matrix_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
    {
        MatrixBufferType* ptr = reinterpret_cast<MatrixBufferType*>(resource.pData);

        ptr->world = XMMatrixTranspose(matrix_buffer.GetWorldMatrix());
        ptr->view = XMMatrixTranspose(matrix_buffer.GetViewMatrix());
        ptr->proj = XMMatrixTranspose(matrix_buffer.GetProjectionMatrix());
        
        m_context->Unmap(matrix_buffer.Get(), 0);
    }

    m_context->VSSetConstantBuffers(0, 1, matrix_buffer.GetAddressOf());
}

void Context::Bind(Mesh& mesh)
{
    UINT stride = mesh.GetVertexBuffer().GetStride();
    UINT offset = mesh.GetVertexBuffer().GetOffset();

    m_context->IASetVertexBuffers(0, 1, mesh.GetVertexBuffer().GetAddressOf(), &stride, &offset);
    m_context->IASetIndexBuffer(mesh.GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
    m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Context::Bind(Material& material) 
{
    m_context->IASetInputLayout(material.GetInputLayout().Get());
    m_context->VSSetShader(material.GetVertexShader().Get(), nullptr, 0);
    m_context->PSSetShader(material.GetPixelShader().Get(), nullptr, 0);
}
