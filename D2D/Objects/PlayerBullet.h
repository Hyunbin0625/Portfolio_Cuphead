#pragma once

class PlayerBullet : public Bullet
{
public:
	PlayerBullet(UINT totalBullet, float bulletSpeed, float speakerSpeed, const wstring& texturePath);

public:
	void CreateBullet();

	void SetPosition(Vector2 position) { this->position = position; }
	void SetRotation(float rotation) { this->rotation = rotation; }

public:
	void Update() override;
	void Render() override;

private:
	wstring texturePath = { 0 };

	Vector2 position;
	float rotation = 0.0f;
};
