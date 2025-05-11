#pragma once
#include <memory>
#include "Scene/Component/Component.h"
#include "Resource/Mesh.h"

class MeshComponent : public Component
{
private:
    std::shared_ptr<Mesh> m_mesh = std::make_shared<Mesh>();

public:
    MeshComponent() = default;
    explicit MeshComponent(std::shared_ptr<Mesh> mesh) : m_mesh(mesh) {}

    std::shared_ptr<Mesh> GetMesh() const { return m_mesh; }
    void SetMesh(std::shared_ptr<Mesh> mesh) { m_mesh = mesh; }
};
