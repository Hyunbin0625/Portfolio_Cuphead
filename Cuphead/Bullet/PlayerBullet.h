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

	void SetIsHit(bool bHit) { this->bHit = bHit; }
	void SetActivation(bool bActivation) { this->bActivation = bActivation; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }

private:
	shared_ptr<AnimationRect> animRect;

	float speed;
	float totalSize;
	int animCount = 0;

	float time = 0.0f;

	bool bHit = false;
	bool bActivation;
};
