#pragma once

enum class WaterType
{
	Water_A,
	Water_B,
	Water_C,
	Water_D
};

class BG_Water
{
public:
	BG_Water() : BG_Water(WaterType::Water_A, Vector2(), 1.0f) {}
	BG_Water(WaterType type, Vector2 position, float size);

public:
	void Update();
	void Render();

	void GUI(int ordinal);

private:
	unique_ptr<AnimationRect> animRect;

	WaterType type = WaterType::Water_A;
	wstring typeName = L"";
	Vector2 position = Vector2();
	float size = 1.0f;

	int currentClip = 0;

	string path = "";
};
