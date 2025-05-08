#pragma once
#include <string>
#include <memory>

#include <d3d11.h>

#include "Resource/ResourceDescriptor.h"

template <typename T, typename DescriptorT>
class IResourceLoader
{
public:
    virtual std::shared_ptr<T> Load(const DescriptorT& descriptor, ID3D11Device* device) = 0;
    virtual bool Supports(const DescriptorT& descriptor) const = 0;
    virtual ~IResourceLoader() = default;
};
