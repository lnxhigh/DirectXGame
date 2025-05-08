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

#include "Scene/Scene.h"

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
    void Render(Scene& scene);

private:
    void BeginFrame(); // Clear and set render target
    void SetupScene(Scene& scene); // Viewport, Camera, Light
    void DrawScene(Scene& scene); // Transform, Material, Mesh
    void EndFrame(); // Present

public:
    Device& GetDevice() { return m_device; }
    Context& GetContext() { return m_context; }
};
