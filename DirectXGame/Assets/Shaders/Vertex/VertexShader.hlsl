#include "../Common/ShaderCommon.hlsl"

VertexOut main(VertexIn input)
{
    VertexOut output;

    float4 local_pos = float4(input.position, 1.0f);
    float4 world_pos = mul(local_pos, world);
    float4 view_pos = mul(world_pos, view);
    float4 proj_pos = mul(view_pos, proj);
    
    output.position = proj_pos;
    output.texcoord = input.texcoord;
    output.color = input.color;
    
    output.world_position = world_pos.xyz;
    output.world_normal = normalize(mul(input.normal, (float3x3)world_inv_transpose));

    return output;
}
