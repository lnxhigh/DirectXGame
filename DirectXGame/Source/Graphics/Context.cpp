#include "Graphics/Context.h"

bool Context::Init(ID3D11DeviceContext* context)
{
    m_context = context;
    return true;
}

