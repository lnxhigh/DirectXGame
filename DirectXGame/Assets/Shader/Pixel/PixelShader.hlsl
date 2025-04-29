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
    float3 ambient = ambient_color.rgb * diffuse_color.rgb;
    float3 diffuse = light_color.rgb * diffuse_color.rgb * max(dot(n, l), 0.0f);
    float3 specular = light_color.rgb * specular_color.rgb * pow(max(dot(n, h), 0.0f), shininess);
    
    return float4(ambient + diffuse + specular, 1.0f);
}
