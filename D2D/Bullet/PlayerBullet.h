#pragma once

class PlayerBullet
{
public:
	PlayerBullet() : PlayerBullet(0.0f) {}
	PlayerBullet(float bulletSpeed);

public:
	void Init(Vector2 position, float rotation);

public:
	void Update();
	void Render();

	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }

	void SetRunTime(float runTime) { this->runTime = runTime; }

private:
	shared_ptr<AnimationRect> animRect;

	float speed;
	float runTime = 0.0f;
};
