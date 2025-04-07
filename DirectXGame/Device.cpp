#include "Device.h"

bool Device::Init()
{
    D3D_FEATURE_LEVEL feature_level;

    HRESULT hr = D3D11CreateDevice(
        0, // default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        0, // no software device
        0,
        0, 0, // default feature level array
        D3D11_SDK_VERSION,
        m_device.GetAddressOf(),
        &feature_level,
        m_context.GetAddressOf()
    );

    if (FAILED(hr))
    {
        OutputDebugStringA("Error: Failed to create D3D11 device");
        return false;
    }

    if (feature_level != D3D_FEATURE_LEVEL_11_0)
    {
        OutputDebugStringA("Error: Direct3D Feature Level 11 unsupported");
        return false;
    }

    return true;
}
