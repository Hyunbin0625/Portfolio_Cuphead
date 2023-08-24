#include "CBuffers.hlsl"

Texture2D sourceTex : register(t0); // texture, 0��°
SamplerState samp : register(s0);   // sampler, 0��°

cbuffer OutlineBuffer : register(b0)
{
    bool _bOutline;
}

float4 PS(PixelInput input) : SV_Target0    // target0���� ���
{
    // smpling
    float4 color = sourceTex.Sample(samp, input.uv);
    
//  if(color.a == 0.0f)
//      discard;    // ���� �����ٴ� ��, ó���ϰ� �ִ� ���� �ȼ�����
    
    float border = 1.0f / 128;
    
    if (_bOutline && (input.uv.x < border || input.uv.x > 1.0f - border || input.uv.y < border || input.uv.y > 1.0f - border))
        color = float4(1, 1, 1, 1);
    
    return color;
};