#include "ShaderCommon.hlsl"

float4 main(PSIn input) : SV_TARGET 
{
    return input.color;
}
