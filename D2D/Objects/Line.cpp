#include "stdafx.h"
#include "Line.h"

Line::Line(const Vector2& position, float length, float rotation, const Color& color)
	: Drawable("Line", position, Vector2(length, 0), rotation, L"_Shaders/Vertex.hlsl")
{
	vertices.assign(2, Vertex());
	vertices[0].position = Vector2(0, 0);
	vertices[1].position = Vector2(1, 0);

	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);

	IL->Create(Vertex::descs, VS->GetBlob());

	AddComponent(make_shared<ColorComponent>(color, 0));
}

void Line::Update()
{
	SUPER::Update();
}

void Line::Render()
{
	SUPER::Render();

	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}
