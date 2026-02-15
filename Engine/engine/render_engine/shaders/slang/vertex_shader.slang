struct VSInput
{
    [[vk::location(0)]]
    float2 inPosition;

    [[vk::location(1)]]
    float3 inColor;
};

struct VSOutput
{
    float4 position : SV_Position;

    [[vk::location(0)]]
    float3 fragColor;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    output.position = float4(input.inPosition, 0.0, 1.0);
    output.fragColor = input.inColor;

    return output;
}
