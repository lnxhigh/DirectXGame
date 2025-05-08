#pragma once
#include "Resource/Loader/IRuntimeResourceLoader.h"

template <typename T, typename DescriptorT>
class ResourceLoaderAdapter : public IRuntimeResourceLoader 
{
    std::unique_ptr<IResourceLoader<T, DescriptorT>> m_loader;

public:
    explicit ResourceLoaderAdapter(std::unique_ptr<IResourceLoader<T, DescriptorT>> loader)
        : m_loader(std::move(loader)) {}

    std::shared_ptr<void> Load(const ResourceDescriptor& descriptor, ID3D11Device* device) override 
    {
        return m_loader->Load(static_cast<const DescriptorT&>(descriptor), device);
    }

    bool Supports(const ResourceDescriptor& descriptor) const override
    {
        return m_loader->Supports(static_cast<const DescriptorT&>(descriptor));
    }
};
