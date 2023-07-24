#pragma once

class Circle : public Drawable
{
public:
	Circle(const Vector2& position, const Vector2& scale, float rotataion, const size_t& segments, const Color& color = RED);

public:
	void Update() override;
	void Render() override;

private:
	vector<Vertex> vertices;
	size_t segments = 0;
};
