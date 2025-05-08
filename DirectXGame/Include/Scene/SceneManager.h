#pragma once
#include <vector>
#include <memory>

#include <d3d11.h>

#include "Scene/Scene.h"

class SceneManager
{
private:
    std::vector<std::unique_ptr<Scene>> m_scenes;

public:
    bool Load(ID3D11DeviceContext* context);

};
