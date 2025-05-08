#pragma once
#include <memory>

#include <d3d11.h>

#include "Resource/ResourceDescriptor.h"

class IRuntimeResourceLoader
{
public:
	virtual std::shared_ptr<void> Load(const ResourceDescriptor& descriptor, ID3D11Device* device) = 0;
    virtual bool Supports(const ResourceDescriptor& descriptor) const = 0;
};
