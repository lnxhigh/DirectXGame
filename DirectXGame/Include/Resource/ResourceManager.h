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

    template <typename T, typename DescriptorT>
    std::shared_ptr<T> Load(const DescriptorT& descriptor, ID3D11Device* device)
    {        
        // Check cache

        std::string key = descriptor.id;

        auto it = m_cache.find(key);
        if (it != m_cache.end())
            return std::static_pointer_cast<T>(it->second);

        // Load resource

        for (auto& loader : m_loaders) {
            if (loader->Supports(descriptor)) {
                auto resource = loader->Load(descriptor, device);
                
                if (!resource) 
                    throw std::runtime_error("Error: Loader failed to load: " + key);

                m_cache[key] = resource;
                return std::static_pointer_cast<T>(resource);
            }
        }

        // Return nullptr if fail to load

        throw std::runtime_error("Error: No loader supports descriptor: " + key);

        return nullptr;
    }

};
