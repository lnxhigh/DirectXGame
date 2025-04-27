#pragma once
#include "Resource/Material.h"
#include "Scene/Component/Component.h"

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
