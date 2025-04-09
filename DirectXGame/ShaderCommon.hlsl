cbuffer MatrixBuffer : register(b0)
{
    matrix world;
    matrix view;
    matrix proj;
};

struct VSIn
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct PSIn
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};
