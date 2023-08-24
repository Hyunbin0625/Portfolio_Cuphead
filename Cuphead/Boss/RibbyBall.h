#pragma once

class RibbyBall
{
public:
	RibbyBall() : RibbyBall(0.0f) {}
	RibbyBall(float bulletSpeed);

public:
	void Init(Vector2 position, float rotation);

public:
	void Update();
	void Render();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	bool GetActivation() { return bActivation; }

	void SetActivation(bool bActivation) { this->bActivation = bActivation; }
	void SetSpeed(float speed) { this->speed = speed; }
	void SetRunTime(float runTime) { this->runTime = runTime; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }

private:
	shared_ptr<AnimationRect> animRect;
	shared_ptr<AnimationRect> sfx;
	bool bActivation = false;

	float speed;
	float runTime = 0.0f;

	float totalSize = 1.0f;
};