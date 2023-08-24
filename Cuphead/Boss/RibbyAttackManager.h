#pragma once

class RibbyAttackManager
{
public:
	RibbyAttackManager();

public:
	void Init(UINT totalBullet, float bulletSpeed, Vector2 position, float rotation, int currentPhase);
	void InitBall();
	void InitCoin(float rotation);

	void Update();
	void Render();

public:
	vector<shared_ptr<RibbyFist>> GetBullets() { return bullets; }
	vector<shared_ptr<RibbyBall>> GetBalls() { return balls; }
	vector<shared_ptr<RibbyCoin>> GetCoins() { return coins; }

	int GetCurrentIndex() { return currentIndex; }
	bool GetEnd() { return bEnd; }

	void SetCurrentIndex(int currentIndex) { this->currentIndex = currentIndex; }
	void SetPosition(Vector2 position) { this->position = position; }
	void SetRotation(float rotation) { this->rotation = rotation; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }
	void SetBulletSpeed(float bulletSpeed) { this->bulletSpeed = bulletSpeed; }

private:
	vector<shared_ptr<RibbyFist>> bullets;
	vector<shared_ptr<RibbyBall>> balls;
	vector<shared_ptr<RibbyCoin>> coins;
	mt19937 mt;

	UINT totalBullet = 0;
	float bulletSpeed = 0;

	// Index
	int currentIndex = 0;
	int parrySlapIndex = 0;

	Vector2 position;
	float rotation = 0.0f;

	float totalSize = 1.0f;

	float time = 0.0f;
	float rebound = 90.0f * totalSize;
	int count = 0;
	bool bUp = true;

	int currentPhase = 1;
	bool bEnd = true;
};