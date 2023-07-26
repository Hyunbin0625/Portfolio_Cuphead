#pragma once

class PlayerSpecialAttackManager
{
public:
	PlayerSpecialAttackManager(UINT totalBullet, float bulletSpeed);

public:
	void CreateBullet();
	void Init(Vector2 position, float rotation);
	void IndexManagement();

	void Update();
	void Render();

	int GetCurrentIndex() { return currentIndex; }
	shared_ptr<PlayerSpecialAttack> GetBullet(int index) { return bullets[index]; }

	void SetCurrentIndex(int currentIndex) { this->currentIndex = currentIndex; }
	void SetPosition(Vector2 position) { this->position = position; }
	void SetRotation(float rotation) { this->rotation = rotation; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }

private:
	vector<shared_ptr<PlayerSpecialAttack>> bullets;
	vector<bool> activation;

	UINT totalBullet;
	float bulletSpeed;

	// Index
	int currentIndex = 0;

	Vector2 position;
	float rotation = 0.0f;

	float totalSize;
};

