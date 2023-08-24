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
    
    float2 arr[8] =
    {
        float2(-1, -1), float2(0, -1),  float2(1, -1),
        float2(-1, 0),                  float2(1, 0),
        float2(-1, 1),  float2(0, 1),   float2(1, 1)
    };
    
    uint blurCount = 0;
    
    blurCount = pow(2, _selection);
    
    float2 texturesSize = float2(1280, 720);    // �ӽ�
    
    for (uint blur = 0; blur < blurCount; ++blur)
    {
        for (uint i = 0; i < 8; ++i)
        {
            float2 uv = arr[i] * (float) blur / texturesSize + input.uv;
            
            color += sourceTex.Sample(samp, uv);
        }
    }
    
    color /= blurCount * 8 + 1;

    return color;
};
