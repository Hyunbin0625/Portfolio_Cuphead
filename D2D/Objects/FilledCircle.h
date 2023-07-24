#pragma once

class FilledCircle : public Drawable
{
public:
	FilledCircle(const Vector2& position, const Vector2& scale, float rotataion, const size_t& segments, const Color& color = RED);

public:
	void Update() override;
	void Render() override;

private:
	vector<Vertex> vertices;

	vector<UINT> indices;
	unique_ptr<IndexBuffer> IB;

	size_t segments = 0;
};
