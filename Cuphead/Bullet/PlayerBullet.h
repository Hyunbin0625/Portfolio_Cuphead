#pragma once

class PlayerBullet
{
public:
	PlayerBullet() : PlayerBullet(0.0f) {}
	PlayerBullet(float bulletSpeed);

public:
	void Init(Vector2 position, float rotation);
	void Hit();

public:
	void Update();
	void Render();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	bool GetActivation() { return bActivation; }
	bool GetHit() { return bHit; }


	void SetActivation(bool bActivation) { this->bActivation = bActivation; }
	void SetRunTime(float runTime) { this->runTime = runTime; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }

private:
	shared_ptr<AnimationRect> animRect;
	bool bActivation;
	bool bHit = true;
	float time = 0.0f;

	float speed;
	float runTime = 0.0f;

	float totalSize;
};