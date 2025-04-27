#pragma once

#include <memory>
#include <vector>

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

#include "Graphics/Buffer/MatrixBuffer.h"
#include "Graphics/Context.h"
#include "Graphics/Device.h"
#include "Graphics/FrameBuffer.h"
#include "Graphics/SwapChain.h"
#include "Graphics/Viewport.h"

#include "Scene/Camera.h"
#include "Scene/Entity/Entity.h"
#include "Scene/Light.h"

class Window;

using Microsoft::WRL::ComPtr;

class Renderer
{
private:
    Device m_device;
    Context m_context;
    SwapChain m_swap_chain;
    FrameBuffer m_frame_buffer;
    MatrixBuffer m_matrix_buffer;
    Viewport m_viewport;

public:
    bool Init(Window* window);
    void Render(const std::vector<std::unique_ptr<Entity>>& entities, Light& light, Camera& camera);

private:
    void BeginFrame(); // Clear and set render target
    void SetupPipeline(Light& light, Camera& camera); // Viewport, Camera, Light
    void DrawScene(const std::vector<std::unique_ptr<Entity>>& entities); // Transform, Material, Mesh
    void EndFrame(); // Present

public:
    Device& GetDevice() { return m_device; }
    Context& GetContext() { return m_context; }
};
