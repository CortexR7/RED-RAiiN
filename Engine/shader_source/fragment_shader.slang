typealias vec1 = float;
typealias vec2 = float2;
typealias vec3 = float3;
typealias vec4 = float4;

struct FSInput
{
    [[vk::location(0)]]
    vec3 fragColor;
};

vec3 GAMMA_ENCODE_RGB(vec3 RGB)
{
    return pow(RGB, 1/2.2);
}

[shader("fragment")]
vec4 main(FSInput input) : SV_Target
{
    for (int i = 0; i < 223456; ++i)
    {
        input.fragColor = GAMMA_ENCODE_RGB(input.fragColor);
    }

    return vec4(input.fragColor, 1.0);
}