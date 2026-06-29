static const float2 positions[3] = {
    float2( 0.0, -0.6),
    float2( 0.6,  0.6),
    float2(-0.6,  0.6)
};

static const float3 colors[3] = {
    float3(0.0, 0.0, 1.0),
    float3(0.0, 1.0, 0.0),
    float3(1.0, 0.0, 0.0)
};

struct VSOutput
{
    float4 position : SV_Position;
    [[vk::location(0)]]
    float3 fragColor;
};

[shader("vertex")]
VSOutput main(uint vertexID : SV_VertexID)
{
    VSOutput output;
    output.position = float4(positions[vertexID], 0.0, 1.0);
    output.fragColor = colors[vertexID];
    return output;
}