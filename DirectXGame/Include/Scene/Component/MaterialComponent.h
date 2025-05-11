#pragma once
#include <memory>
#include "Scene/Component/Component.h"
#include "Resource/Material.h"

class MaterialComponent : public Component
{
private:
    std::shared_ptr<Material> m_material = std::make_shared<Material>();

public:
    MaterialComponent() = default;
    explicit MaterialComponent(std::shared_ptr<Material> material) : m_material(material) {}

    std::shared_ptr<Material> GetMaterial() const { return m_material; }
    void SetMaterial(std::shared_ptr<Material> material) { m_material = material; }
};
