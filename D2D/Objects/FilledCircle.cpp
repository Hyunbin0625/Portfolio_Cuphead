#include "stdafx.h"
#include "FilledCircle.h"

FilledCircle::FilledCircle(const Vector2& position, const Vector2& scale, float rotataion, const size_t& segments, const Color& color)
	: Drawable("FilledCircle", position, scale, rotation, L"_Shaders/Vertex.hlsl"), segments(segments)
{
	vertices.assign(segments + 1, Vertex());
	vertices[0].position = Vector2();

	for (size_t i = 1; i <= segments; ++i)
	{
		float theta = 2 * XM_PI * i / segments;

		vertices[i].position = Vector2(cosf(theta), -sinf(theta)) * 0.5f;
	}

	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);

	indices.assign(segments * 3, sizeof(UINT));

	for (size_t i = 0; i < segments; ++i)
	{
		indices[i * 3] = 0;
		indices[i * 3 + 1] = (UINT)i + 1;
		indices[i * 3 + 2] = (UINT)i + 2;
	}
	indices.back() = 1;

	IB = make_unique<IndexBuffer>();
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	IL->Create(Vertex::descs, VS->GetBlob());

	AddComponent(make_shared<ColorComponent>(color, 0));
}

void FilledCircle::Update()
{
	SUPER::Update();
}

void FilledCircle::Render()
{
	SUPER::Render();

	IB->SetIA();

	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, IB->GetCount());
}
