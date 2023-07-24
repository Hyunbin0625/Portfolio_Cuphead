#pragma once

class Line : public Drawable
{
public:
	Line(const Vector2& position, float length, float rotation, const Color& color = RED);

public:
	void Update() override;
	void Render() override;

private:
	vector<Vertex> vertices;
};
