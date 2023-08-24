#pragma once

enum class CloudType
{
	Clouds_A,
	Clouds_B,
	Clouds_C
};

class BG_Cloud
{
public:
	BG_Cloud() : BG_Cloud(CloudType::Clouds_A, Vector2(), 10.0f, 1.0f) {}
	BG_Cloud(CloudType type, Vector2 position, float speed, float size);

public:
	void Update();
	void Render();

	void GUI(int ordinal);

private:
	vector<unique_ptr<TextureRect>> textureRectList;

	CloudType type = CloudType::Clouds_A;
	Vector2 position = Vector2();
	float speed = 10.0f;
	float size = 1.0f;

	string path = "";
};
