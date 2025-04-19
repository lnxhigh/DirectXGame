#include "Context.h"
#include "Viewport.h"
#include "LightBuffer.h"
#include "Mesh.h"
#include "Material.h"

bool Context::Init(ID3D11DeviceContext* context)
{
    m_context = context;
    return true;
}

