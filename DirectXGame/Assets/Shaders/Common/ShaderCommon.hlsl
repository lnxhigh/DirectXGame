// MatrixBuffer : b0
// world, view, projection matrix

cbuffer MatrixBuffer : register(b0)
{
    matrix world;
    matrix view;
    matrix proj;
    
    matrix world_inv_transpose;
};

// LightBuffer : b1
// Directional light

cbuffer LightBuffer : register(b1)
{
    float4 light_color; // color + intensity
    float3 light_direction;
    float padding_light_direction;
    float4 ambient_color;
}

// MaterialBuffer : b2
// Material properties

cbuffer MaterialBuffer : register(b2)
{
    float4 diffuse_color;
    float4 specular_color;
    float shininess;
    float3 padding_shininess;
}

// CameraBuffer : b3
// Camera Position

cbuffer CameraBuffer : register(b3)
{
    float3 camera_position;
    float padding_camera_position;
}

// Diffuse Map

Texture2D DiffuseMap : register(t0);

// Sampler State

SamplerState Sampler : register(s0);

// VertexIn VertexOut PixelIn

struct VertexIn
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD0;
    float4 color : COLOR;
};

struct VertexOut
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
    float4 color : COLOR;
    
    float3 world_position: TEXCOORD1;
    float3 world_normal : TEXCOORD2;
};

typedef VertexOut PixelIn;
