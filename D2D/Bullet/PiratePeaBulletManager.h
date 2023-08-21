#pragma once

class PiratePeaBullet
{
public:
	PiratePeaBullet();

public:
	void Init(Vector2 position, float rotation, float speed, bool bParry);

public:
	void Update();
	void Render();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	bool GetActivation() { return bActivation; }
	bool GetDeath() { return bDeath; }
	bool GetParrySlap() { return bParrySlap; }

	void SetActivation(bool bActivation) { this->bActivation = bActivation; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }
	void SetDeath(float bDeath) { this->bDeath = bDeath; }

private:
	shared_ptr<AnimationRect> animRect;

	float speed = 0.0f;
	float totalSize = 1.0f;

	bool bParrySlap = false;
	bool bDeath = false;
	bool bActivation = false;
};

class PiratePeaBulletManager
{
public:
	DECLARE_SINGLETON(PiratePeaBulletManager);

public:
	void CreateBullet();
	void Init(Vector2 position, float rotation, float speed);
	void IndexManagement();

	void Update();
	void Render();

public:
	vector<shared_ptr<PiratePeaBullet>> GetBullets() { return bullets; }

	int GetCurrentIndex() { return currentIndex; }

	void SetCurrentIndex(int currentIndex) { this->currentIndex = currentIndex; }
	void SetPosition(Vector2 position) { this->position = position; }
	void SetRotation(float rotation) { this->rotation = rotation; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }

private:
	vector<shared_ptr<PiratePeaBullet>> bullets;
	mt19937 mt;

	// Index
	int currentIndex = 0;

	Vector2 position = Vector2();
	float rotation = 0.0f;
	float totalSize = 1.0f;
	float speed = 0.0f;
};
