#include "Resource/Loader/ShaderLoader.h"

#include <filesystem>

std::shared_ptr<Shader> ShaderLoader::Load(const ShaderDescriptor& descriptor, ID3D11Device* device)
{
	std::shared_ptr<Shader> shader = std::make_shared<Shader>();
	
	if (!shader->Init(device, descriptor))
	{
		OutputDebugStringA("Error: shader init fail\n");
	}

	return shader;
}

bool ShaderLoader::Supports(const ShaderDescriptor& descriptor) const
{
	if (descriptor.type != "shader")
		return false;

	return true;
}
