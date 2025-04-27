#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "Scene/Component/Component.h"

class Entity 
{
private:
    // Entity owns its own components
    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_components;

public:
    Entity() = default;

    template <typename T, typename... Args>
    T* AddComponent(Args&&... args) 
    {
        static_assert(std::is_base_of<Component, T>::value, "Error: T must be a Component");

        // Check if duplicated
        if (HasComponent<T>())
            return GetComponent<T>();

        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T* ptr = component.get();
        m_components[typeid(T)] = std::move(component); // Transfer ownership of a component
        
        return ptr;
    }

    template <typename T>
    T* GetComponent() const
    {
        auto it = m_components.find(typeid(T));

        if (it != m_components.end()) 
            return static_cast<T*>(it->second.get());

        return nullptr;
    }

    template <typename T>
    bool HasComponent() const 
    {
        return m_components.find(typeid(T)) != m_components.end();
    }
};
