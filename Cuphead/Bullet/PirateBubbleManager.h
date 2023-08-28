#pragma once

class PirateBubble
{
public:
	PirateBubble();

public:
	void Init(Vector2 position, float rotation, float totalSize, float speed, float range);

public:
	void Update();
	void Render();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }

	bool GetActivation() { return bActivation; }

	void SetActivation(bool bActivation) { this->bActivation = bActivation; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }

	void SetIsEnd(bool bEnd) { this->bEnd = bEnd; }

private:
	shared_ptr<AnimationRect> animRect;
	float rotate = 0.1f;
	Vector2 rotatePos = Vector2();
	float range = 0.0f;

	Vector2 position = Vector2();
	bool check = false;
	int count = 0;
	float speed = 0.0f;
	float totalSize = 1.0f;

	bool bEnd = false;
	bool bActivation = false;
};

class PirateBubbleManager
{
public:
	DECLARE_SINGLETON(PirateBubbleManager);

public:
	void CreateBullet();
	void IndexManagement(Vector2 position, float rotation, float totalSize, float speed, float range);

	void Update();
	void Render();

public:
	vector<shared_ptr<PirateBubble>> GetBullets() { return bullets; }

	int GetCurrentIndex() { return currentIndex; }

	void SetCurrentIndex(int currentIndex) { this->currentIndex = currentIndex; }
	void SetPosition(Vector2 position) { this->position = position; }
	void SetRotation(float rotation) { this->rotation = rotation; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }

private:
	vector<shared_ptr<PirateBubble>> bullets;

	// Index
	int currentIndex = 0;

	Vector2 position = Vector2();
	float rotation = 0.0f;
	float totalSize = 1.0f;
	float speed = 0.0f;
};
