#pragma once

class PlayerBulletManager
{
public:
	PlayerBulletManager(UINT totalBullet, float bulletSpeed, float speakerSpeed);

public:
	void CreateBullet();
	void Init(Vector2 position, float rotation, float rebound);
	void IndexManagement();

	void Update();
	void Render();

public:
	vector<shared_ptr<PlayerBullet>> GetBullets() { return bullets; }
	int GetNextIndex() { return nextIndex; }
	float GetTime() { return time; }
	int GetLastIndex() { return lastIndex; }
	float GetSpeakerSpeed() { return speakerSpeed; }
	shared_ptr<PlayerBullet> GetBullet(int index) { return bullets[index]; }

	void SetNextIndex(int nextIndex) { this->nextIndex = nextIndex; }
	void SetTime(float time) { this->time = time; }
	void SetLastIndex(int lastIndex) { this->lastIndex = lastIndex; }
	void SetSpeakerSpeed(float speakerSpeed) { this->speakerSpeed = speakerSpeed; }
	void SetPosition(Vector2 position) { this->position = position; }
	void SetRotation(float rotation) { this->rotation = rotation; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }

private:
	vector<shared_ptr<PlayerBullet>> bullets;

	UINT totalBullet;
	float bulletSpeed;
	float speakerSpeed;

	// Index
	int nextIndex = 0;
	float time = 0;	// time
	int lastIndex = -1;	// last Index

	Vector2 position;
	float rotation = 0.0f;

	float totalSize;

	int count = 1;		// -1 ~ 1
	bool bCount = 0;
};

