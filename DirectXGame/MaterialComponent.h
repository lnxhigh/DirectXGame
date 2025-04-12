#pragma once
#include "Component.h"
#include "Material.h"

class MaterialComponent : public Component
{
private:
    Material* m_material = nullptr;

public:
    MaterialComponent() = default;
    explicit MaterialComponent(Material* material) : m_material(material) {}

    Material* GetMaterial() const { return m_material; }
    void SetMaterial(Material* material) { m_material = material; }
};
