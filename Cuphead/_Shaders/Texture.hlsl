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

cbuffer TransformBuffer : register(b0) // buffer, 0��°
{
    matrix _world;
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

float4 PS(PixelInput input) : SV_Target0    // target0���� ���
{
    // smpling
    float4 color = sourceTex.Sample(samp, input.uv);
    
//  if(color.a == 0.0f)
//      discard;    // ���� �����ٴ� ��, ó���ϰ� �ִ� ���� �ȼ�����
    
    return color;
};