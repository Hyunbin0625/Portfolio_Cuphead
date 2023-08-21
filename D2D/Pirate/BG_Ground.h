#pragma once

class BG_Ground
{
public:
	BG_Ground() : BG_Ground(Vector2(), Vector2(), 1.0f) {}
	BG_Ground(Vector2 position, Vector2 addTopPos, float size);

public:
	void Update();
	void BRender();
	void FRender();

	void GUI();

private:
	unique_ptr<TextureRect> textureRect;
	unique_ptr<TextureRect> topTextureRect;

	Vector2 position = Vector2();
	Vector2 addPos = Vector2();
	float size = 1.0f;
};
