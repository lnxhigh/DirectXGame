#include "../Common/ShaderCommon.hlsl"

float4 main(PixelIn input) : SV_TARGET 
{
    // Surface normal
    float3 n = normalize(input.world_normal);

    // Light direction
    float3 l = normalize(-light_direction);

    // View direction
    float3 v = normalize(camera_position - input.world_position);

    // Half vector (Blinn-Phong)
    float3 h = normalize(l + v);

    // Compute color
    float4 diffuse_map_color = DiffuseMap.Sample(Sampler, input.texcoord);
    
    float3 diffuse = light_diffuse.rgb * diffuse_map_color.rgb * max(dot(n, l), 0.0f);
    float3 specular = light_specular.rgb * specular_color.rgb * pow(max(dot(n, h), 0.0f), shininess);
    float3 ambient = light_ambient.rgb * ambient_color.rgb * diffuse_map_color.rgb;
    float3 emissive = emissive_color.rgb;
    
    return float4(diffuse + specular + ambient + emissive, 1.0f);
}
