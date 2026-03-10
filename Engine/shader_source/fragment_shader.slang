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
    output.outColor.x = 1.78f * sin(output.outColor.y * 5 * output.outColor.x);
    output.outColor.y = -4.05f * cos(output.outColor.y * 5 * output.outColor.z);
    output.outColor.z = 2.45f * tan(output.outColor.z * 5 * output.outColor.x);
    return output;
}
