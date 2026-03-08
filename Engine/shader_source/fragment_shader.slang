struct FSInput
{
    [[vk::location(0)]]
    float3 fragColor;
};

struct FSOutput
{
    [[vk::location(0)]]
    float4 outColor;
};

[shader("fragment")]
FSOutput main(FSInput input)
{
    FSOutput output;
    output.outColor = float4(input.fragColor, 1.0);
    return output;
}
