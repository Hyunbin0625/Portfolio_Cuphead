#pragma once

class PlayerSpecialAttack
{
public:
	PlayerSpecialAttack() : PlayerSpecialAttack(0.0f) {}
	PlayerSpecialAttack(float bulletSpeed);

public:
	void Init(Vector2 position, float rotation);

public:
	void Update();
	void Render();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	bool GetActivation() { return bActivation; }

	void SetActivation(bool bActivation) { this->bActivation = bActivation; }
	void SetRunTime(float runTime) { this->runTime = runTime; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }

private:
	shared_ptr<AnimationRect> animRect;
	bool bActivation;

	float speed;
	float runTime = 0.0f;

	float totalSize;
};
