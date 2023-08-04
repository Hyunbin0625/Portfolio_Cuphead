#pragma once

class LobberSeed
{
public:
	LobberSeed() : LobberSeed(0.0f) {}
	LobberSeed(float bulletSpeed);

public:
	void Init(Vector2 position, float rotation, float playerX);

public:
	void Update();
	void Render();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	bool GetActivation() { return bActivation; }

	void SetActivation(bool bActivation) { this->bActivation = bActivation; }
	void SetSpeed(float speed) { this->speed = speed; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }
	void SetGround(bool bGround) { this->bGround = bGround; }

private:
	shared_ptr<AnimationRect> animRect;
	bool bActivation;

	float speed;
	float space = 0;

	Vector2 position;
	float totalSize;

	float G = 0;
	float jumpSpeed = 0.0f;
	float playerX = 0.0f;

	bool bGround = false;
};

class LSeedManager
{
public:
	LSeedManager(UINT totalBullet, float bulletSpeed);

public:
	void CreateBullet();
	void Init(Vector2 position, float rotation, float playerX);
	void IndexManagement();

	void Update();
	void Render();

public:
	shared_ptr<LobberSeed> GetBullet(int index) { return bullets[index]; }
	vector<shared_ptr<LobberSeed>> GetBullets() { return bullets; }

	int GetCurrentIndex() { return currentIndex; }

	void SetCurrentIndex(int currentIndex) { this->currentIndex = currentIndex; }
	void SetPosition(Vector2 position) { this->position = position; }
	void SetRotation(float rotation) { this->rotation = rotation; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }
	void SetBulletSpeed(float bulletSpeed) { this->bulletSpeed = bulletSpeed; }

private:
	vector<shared_ptr<LobberSeed>> bullets;

	UINT totalBullet;
	float bulletSpeed;

	// Index
	int currentIndex = 0;

	Vector2 position;
	float rotation = 0.0f;

	float totalSize;

	float playerX = 0.0f;
};