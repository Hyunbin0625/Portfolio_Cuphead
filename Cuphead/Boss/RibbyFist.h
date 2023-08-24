#pragma once

class RibbyFist
{
public:
	RibbyFist() : RibbyFist(0.0f) {}
	RibbyFist(float bulletSpeed);

public:
	void Init(Vector2 position, float rotation);

public:
	void Update();
	void Render();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	bool GetActivation() { return bActivation; }
	bool GetParrySlap() { return bParrySlap; }

	void SetActivation(bool bActivation) { this->bActivation = bActivation; }
	void SetSpeed(float speed) { this->speed = speed; }
	void SetRunTime(float runTime) { this->runTime = runTime; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }
	void SetParrySlap(bool bParrySlap) { this->bParrySlap = bParrySlap; }

private:
	shared_ptr<AnimationRect> animRect;
	bool bActivation;

	float speed;
	float runTime = 0.0f;

	float totalSize = 1.0f;

	bool bParrySlap = false;
};