struct FSInput
{
    [[vk::location(0)]]
    float3 fragColor;
};

[shader("fragment")]
float4 main(FSInput input) : SV_Target
{
    return float4(input.fragColor, 1.0);
}