#pragma once

class PirateCannonBall
{
public:
	PirateCannonBall();

public:
	void Init(Vector2 position, float rotation, float speed);

public:
	void Update();
	void Render();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	shared_ptr<ColorRect> GetColorRect() { return collisionRect; }

	bool GetActivation() { return bActivation; }

	void SetActivation(bool bActivation) { this->bActivation = bActivation; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }

private:
	shared_ptr<AnimationRect> animRect;
	shared_ptr<AnimationRect> SFX;
	shared_ptr<ColorRect> collisionRect;

	float speed = 0.0f;
	float totalSize = 1.0f;

	bool bActivation = false;
	bool bSFX = false;
};

class PirateCannonBallManager
{
public:
	DECLARE_SINGLETON(PirateCannonBallManager);

public:
	void CreateBullet();
	void Init(Vector2 position, float rotation, float speed);
	void IndexManagement();

	void Update();
	void Render();

public:
	vector<shared_ptr<PirateCannonBall>> GetBullets() { return bullets; }

	int GetCurrentIndex() { return currentIndex; }

	void SetCurrentIndex(int currentIndex) { this->currentIndex = currentIndex; }
	void SetPosition(Vector2 position) { this->position = position; }
	void SetRotation(float rotation) { this->rotation = rotation; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }

private:
	vector<shared_ptr<PirateCannonBall>> bullets;

	// Index
	int currentIndex = 0;

	Vector2 position = Vector2();
	float rotation = 0.0f;
	float totalSize = 1.0f;
	float speed = 0.0f;
};
