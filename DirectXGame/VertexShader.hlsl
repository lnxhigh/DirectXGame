#include "ShaderCommon.hlsl"

PSIn main(VSIn input)
{
    PSIn output;

    float4 local_pos = float4(input.position, 1.0f);
    float4 world_pos = mul(local_pos, world);
    float4 view_pos  = mul(world_pos, view);
    float4 proj_pos  = mul(view_pos, proj);

    output.position = proj_pos;
    output.color = input.color;

    return output; // Clip space
}
