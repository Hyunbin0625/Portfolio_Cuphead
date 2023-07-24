struct VertexInput
{
    float4 position : POSITION0;
};

struct PixelInput
{
    float4 position : SV_POSITION0; // �ȼ� ��ġ�� �����ϴ� Semantics
};

cbuffer World : register(b0) // buffer, 0��°
{
    matrix _world;
}

cbuffer ViewProjection : register(b1) // buffer, 0��°
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
    
    return output;
}

cbuffer ColorBuffer : register(b0)
{
    float4 _color;
}

float4 PS(PixelInput input) : SV_Target0    // target0���� ���
{
    return _color;
};