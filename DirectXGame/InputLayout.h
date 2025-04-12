#pragma once
#include <d3d11.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

class InputLayout
{
private:
	ComPtr<ID3D11InputLayout> m_input_layout = nullptr;
	
public:
	bool Create(ID3D11Device* device, void* shader_byte_code, SIZE_T size_byte_code);
	ID3D11InputLayout* Get() const { return m_input_layout.Get(); }
};

