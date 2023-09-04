#pragma once

class CroaksAttackManager
{
public:
	DECLARE_SINGLETON(CroaksAttackManager);

public:
	// Firefly
	void CreateBullet(int addSize);
	void InitBullet(UINT maxBullet, float bulletSpeed);
	void InitSize();
	void InitPos(Vector2 position);

	// Platform
	void InitPlatform(Vector2 position, float speed, SlotType type);
	void CreatePlatform();

public:
	void Update();
	void Render();

	void GUI();

	void FireFlyGUI();
	void PSnakeGUI();
	void PTigerGUI();
	void PBisonGUI();

public:	// Firefly
	vector<shared_ptr<CroaksFirefly>> GetBullets() { return bullets; }

	int GetCurrentIndex() { return currentIndex; }

	int Remainder() { return indexSize - count; }

	void SetCurrentIndex(int currentIndex) { this->currentIndex = currentIndex; }
	void SetPosition(Vector2 position) { this->position = position; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }
	void SetBulletSpeed(float bulletSpeed) { this->bulletSpeed = bulletSpeed; }
	void SetPlatform(bool bPlatform) { this->bPlatform = bPlatform; }

public:	// Platform
	vector<shared_ptr<CroaksPSnake>> GetPSnakeList() { return pSnakeList; }
	vector<shared_ptr<CroaksPTiger>> GetPTigerList() { return pTigerList; }
	vector<shared_ptr<CroaksPBison>> GetPBisonList() { return pBisonList; }
	void SetGroundY(float groundY) { this->groundY = groundY; }

	bool GetEnd() { return bEnd; }

private:
	vector<shared_ptr<CroaksFirefly>> bullets;

	vector<shared_ptr<CroaksPSnake>> pSnakeList;
	vector<shared_ptr<CroaksPTiger>> pTigerList;
	vector<shared_ptr<CroaksPBison>> pBisonList;

	SlotType type = SlotType::None;
	mt19937 mt;

	UINT totalIndex = 0;
	UINT maxBullet = 0;

	float bulletSpeed = 0.0f;

	// Index
	int currentIndex = 0;
	int indexSize = 0;
	int count = 0;

	Vector2 createPos = Vector2();
	Vector2 position = Vector2();
	float totalSize = 1.0f;
	float time = 0.0f;
	float regenTime = 0.0f;

	float groundY = 0.0f;
	float addGroundY = 129.79f;

	bool bEnd = false;
	bool bPlatform = false;
};
