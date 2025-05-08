#pragma once
#include <filesystem>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>

#include <d3d11.h>

#include "Resource/Loader/IResourceLoader.h"
#include "Resource/Loader/IRuntimeResourceLoader.h"
#include "Resource/Loader/ResourceLoaderAdapter.h"

class ResourceManager
{
private:
    std::vector<std::unique_ptr<IRuntimeResourceLoader>> m_loaders;
    std::unordered_map<std::string, std::shared_ptr<void>> m_cache;

public:
    template <typename T, typename DescriptorT>
    void RegisterLoader(std::unique_ptr<IResourceLoader<T, DescriptorT>> loader) 
    {
        m_loaders.emplace_back(std::make_unique<ResourceLoaderAdapter<T, DescriptorT>>(std::move(loader)));
    }

    std::shared_ptr<void> Load(const ResourceDescriptor& descriptor, ID3D11Device* device) 
    {
        // Check cache

        auto it = m_cache.find(descriptor.id);
        if (it != m_cache.end())
            return it->second;

        // Load resource

        for (auto& loader : m_loaders) {
            if (loader->Supports(descriptor)) {
                auto ptr = loader->Load(descriptor, device);
                
                if (!ptr) 
                    throw std::runtime_error("Error: Loader failed to load: " + descriptor.id);

                m_cache[descriptor.id] = ptr;
                return ptr;
            }
        }

        // Return nullptr if fail to load

        throw std::runtime_error("Error: No loader supports descriptor: " + descriptor.id);

        return nullptr;
    }

};
