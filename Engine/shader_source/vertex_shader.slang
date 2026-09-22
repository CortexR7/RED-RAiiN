typealias vec1 = float;
typealias vec2 = float2;
typealias vec3 = float3;
typealias vec4 = float4;
typealias mat4 = float4x4;


struct RE2_UBO
{
    column_major mat4 MODEL;
    column_major mat4 VIEW;
    column_major mat4 PROJECTION;
};

struct VSInput
{
    [[vk::location(0)]] vec2 position;
    [[vk::location(1)]] vec3 rgb;
};

struct VSOutput
{
    float4 position : SV_Position;
    [[vk::location(0)]] float3 fragColor;
};

[vk::binding(0,0)]
ConstantBuffer<RE2_UBO> ubo;

// WARNING: This function takes in a mat4 that is in row_major and converts it to column_major
// This function is obsolete now since there is a simple keyword that can be added to adress this issue.
mat4 S_MATRIX_TO_G_MATRIX(mat4 M_S)
{
    mat4 M_G;

    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            M_G[j][i] = M_S[i][j];
        }
    }
    return M_G;
}

[shader("vertex")]
VSOutput main(VSInput input)
{
    mat4 PROJ = ubo.PROJECTION;
    mat4 VIEW = ubo.VIEW;
    mat4 MODEL = ubo.MODEL;

    vec4 p = vec4(input.position, 0.0, 1.0);
    mat4 TEMP = mul(PROJ, VIEW);
    TEMP = mul(TEMP, MODEL);
    p = mul(TEMP, p);

    VSOutput output;
    output.position = p;
    output.fragColor = input.rgb;
    return output;
}
