#pragma once
#include "Component.h"
#include "Mesh.h"

class MeshComponent : public Component 
{
private:
    Mesh* m_mesh = nullptr;

public:
    MeshComponent() = default;
    explicit MeshComponent(Mesh* mesh) : m_mesh(mesh) {}

    Mesh* GetMesh() const { return m_mesh; }
    void SetMesh(Mesh* mesh) { m_mesh = mesh; }
};