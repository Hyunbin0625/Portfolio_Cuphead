#include "stdafx.h"
#include "Circle.h"

Circle::Circle(const Vector2& position, const Vector2& scale, float rotataion, const size_t& segments, const Color& color)
	: Drawable("Circle", position, scale, rotation, L"_Shaders/Vertex.hlsl"), segments(segments)
{
	vertices.assign(segments + 1, Vertex());

	for (size_t i = 0; i <= segments; ++i)
	{
		float theta = 2 * XM_PI * i / segments;

		vertices[i].position = Vector2(cosf(theta), -sinf(theta)) * 0.5f;
	}

	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);

	IL->Create(Vertex::descs, VS->GetBlob());

	AddComponent(make_shared<ColorComponent>(color, 0));
}

void Circle::Update()
{
	SUPER::Update();
}

void Circle::Render()
{
	SUPER::Render();

	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
}
