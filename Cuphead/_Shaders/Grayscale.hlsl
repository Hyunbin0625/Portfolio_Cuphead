struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : TEXCOORD0;
};

struct PixelInput
{
    float4 position : SV_POSITION0; // �ȼ� ��ġ�� �����ϴ� Semantics
    float2 uv : TEXCOORD0;
};

cbuffer World : register(b0) // buffer, 0��°
{
    matrix _world;
}

cbuffer ViewProjection : register(b1) // buffer, 1��°
{
    matrix _view;
    matrix _proj;
}

PixelInput VS(VertexInput input)
{
    PixelInput output;
    
//  output.position = input.position;
    // ���� ��ȯ, �� ��ȯ, �������� ��ȯ
    output.position = mul(input.position, _world);  // ���� input�� position�� ���� world�� ����, ���� ��ȯ�� output�� position�� ����.
    output.position = mul(output.position, _view);  // ���� ��ȯ�� output�� position�� ���� view�� ����, �亯ȯ�� output�� position�� ����.
    output.position = mul(output.position, _proj);  // �� ��ȯ�� output�� position�� ���� projection�� ����, �������� ��ȯ�� output�� position�� ����.
    
    output.uv = input.uv;
    
    return output;
}

Texture2D sourceTex : register(t0); // texture, 0��°
SamplerState samp : register(s0);   // sampler, 0��°

cbuffer SelectionBuffer : register(b0)
{
    uint _selection;
}

float4 PS(PixelInput input) : SV_Target0    // target0���� ���
{
    // smpling
    float4 color = sourceTex.Sample(samp, input.uv);
    float3 grayscale = 0;
    float3 sepia = 0;
    
    if (color.a == 0)
        return color;
    
    if (_selection == 2)
    {
        grayscale = (color.r + color.g + color.b) / 3.0f;
        color = float4(grayscale, 1);
    }
    else if (_selection == 3)
    {
        grayscale = dot(color.rgb, float3(0.299f, 0.587f, 0.114f));
        color = float4(grayscale, 1);
    }
    else if (_selection == 4)
    {
        sepia.r = dot(color.rgb, float3(0.393f, 0.769f, 0.189f));
        sepia.g = dot(color.rgb, float3(0.349f, 0.686f, 0.168f));
        sepia.b = dot(color.rgb, float3(0.272f, 0.534f, 0.131f));
        color = float4(sepia.rgb, 1);
    }
    
    return color;
};
