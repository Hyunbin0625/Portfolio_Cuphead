#pragma once

class CroaksAttackManager
{
public:
	CroaksAttackManager(UINT maxBullet, float bulletSpeed);

public:
	void CreateBullet(int addSize);
	void InitSize();
	void InitPos(Vector2 position);

	void Update();
	void Render();

public:
	shared_ptr<CroaksFirefly> GetBullet(int index) { return bullets[index]; }
	vector<shared_ptr<CroaksFirefly>> GetBullets() { return bullets; }

	int GetCurrentIndex() { return currentIndex; }

	int Remainder() { return indexSize - count; }

	void SetCurrentIndex(int currentIndex) { this->currentIndex = currentIndex; }
	void SetPosition(Vector2 position) { this->position = position; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }
	void SetBulletSpeed(float bulletSpeed) { this->bulletSpeed = bulletSpeed; }

private:
	vector<shared_ptr<CroaksFirefly>> bullets;
	mt19937 mt;

	UINT totalIndex = 0;
	UINT maxBullet = 0;

	float bulletSpeed = 0.0f;

	// Index
	int currentIndex = 0;
	int indexSize = 0;
	int count = 0;

	Vector2 position = Vector2();
	float totalSize = 1.0f;
	float time = 0.0f;
};
