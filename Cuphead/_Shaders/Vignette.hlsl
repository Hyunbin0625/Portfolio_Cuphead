struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : TEXCOORD0;
};

struct PixelInput
{
    float4 position : SV_POSITION0; // 픽셀 위치를 설명하는 Semantics
    float2 uv : TEXCOORD0;
};

cbuffer World : register(b0) // buffer, 0번째
{
    matrix _world;
}

cbuffer ViewProjection : register(b1) // buffer, 1번째
{
    matrix _view;
    matrix _proj;
}

PixelInput VS(VertexInput input)
{
    PixelInput output;
    
//  output.position = input.position;
    // 월드 변환, 뷰 변환, 프로젝션 변환
    output.position = mul(input.position, _world);  // 들어온 input의 position에 들어온 world를 곱해, 월드 변환한 output의 position에 들어간다.
    output.position = mul(output.position, _view);  // 월드 변환된 output의 position에 들어온 view를 곱해, 뷰변환한 output의 position에 들어간다.
    output.position = mul(output.position, _proj);  // 뷰 변환된 output의 position에 들어온 projection을 곱해, 프로젝션 변환한 output의 position에 들어간다.
    
    output.uv = input.uv;
    
    return output;
}

Texture2D sourceTex : register(t0); // texture, 0번째
SamplerState samp : register(s0);   // sampler, 0번째

cbuffer SelectionBuffer : register(b0)
{
    uint _selection;
}

float4 PS(PixelInput input) : SV_Target0    // target0번에 출력
{
    // sampling
    float4 color = sourceTex.Sample(samp, input.uv);

    float2 uv = input.uv - 0.5f;
    float x = 5.0f;
 
    color.rgb *= 1 - dot(uv, uv) * x * (_selection - 1);
    
    return color;
};
