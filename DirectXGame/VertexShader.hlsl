#include "ShaderCommon.hlsl"

VSOut main(VSIn input) {
    VSOut output;
    output.position = float4(input.position, 1.0f);
    return output; // Clip Space
}
