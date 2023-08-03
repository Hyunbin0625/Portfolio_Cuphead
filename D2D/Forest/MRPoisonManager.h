#pragma once

class MushroomPoison
{
public:
	MushroomPoison() : MushroomPoison(0.0f) {}
	MushroomPoison(float bulletSpeed);

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
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }
	void SetParrySlap(float bParrySlap) { this->bParrySlap = bParrySlap; }


private:
	shared_ptr<AnimationRect> animRect;
	bool bActivation;

	float speed;

	float totalSize;
	bool bParrySlap;
};

class MRPoisonManager
{
public:
	MRPoisonManager(UINT totalBullet, float bulletSpeed);

public:
	void CreateBullet();
	void Init(Vector2 position, float rotation);
	void IndexManagement();

	void Update();
	void Render();

public:
	shared_ptr<MushroomPoison> GetBullet(int index) { return bullets[index]; }
	vector<shared_ptr<MushroomPoison>> GetBullets() { return bullets; }

	int GetCurrentIndex() { return currentIndex; }

	void SetCurrentIndex(int currentIndex) { this->currentIndex = currentIndex; }
	void SetPosition(Vector2 position) { this->position = position; }
	void SetRotation(float rotation) { this->rotation = rotation; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }
	void SetBulletSpeed(float bulletSpeed) { this->bulletSpeed = bulletSpeed; }

private:
	vector<shared_ptr<MushroomPoison>> bullets;
	mt19937 mt;

	UINT totalBullet;
	float bulletSpeed;

	// Index
	int currentIndex = 0;

	Vector2 position;
	float rotation = 0.0f;

	float totalSize;
};