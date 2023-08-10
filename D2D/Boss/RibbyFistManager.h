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

class RibbyFistManager
{
public:
	RibbyFistManager(UINT totalBullet, float bulletSpeed, float rebound);

public:
	void Init(Vector2 position, float rotation);

	void Update();
	void Render();

public:
	shared_ptr<RibbyFist> GetBullet(int index) { return bullets[index]; }
	vector<shared_ptr<RibbyFist>> GetBullets() { return bullets; }

	int GetCurrentIndex() { return currentIndex; }
	bool GetEnd() { return bEnd; }

	void SetCurrentIndex(int currentIndex) { this->currentIndex = currentIndex; }
	void SetPosition(Vector2 position) { this->position = position; }
	void SetRotation(float rotation) { this->rotation = rotation; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }
	void SetBulletSpeed(float bulletSpeed) { this->bulletSpeed = bulletSpeed; }

private:
	vector<shared_ptr<RibbyFist>> bullets;
	mt19937 mt;

	UINT totalBullet;
	float bulletSpeed;

	// Index
	int currentIndex = 0;
	int parrySlapIndex = 0;

	Vector2 position;
	float rotation = 0.0f;

	float totalSize;

	float time = 0.0f;
	float rebound = 0.0f;
	int count = 0;
	bool bUp = true;

	bool bEnd = true;
};