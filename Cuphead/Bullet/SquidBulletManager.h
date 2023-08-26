#pragma once

class SquidBullet
{
public:
	SquidBullet();

public:
	void Collision(shared_ptr<Player> player);
	void Init(Vector2 position, float size, float speed, float jumpSpeed, float aclrt);

	void Update();
	void Render();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	bool GetActivation() { return bActivation; }
	float GetAclrt() { return aclrt; }
	
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }
	void SetSpeed(float speed) { this->speed = speed; }

	void SetAclrt(float aclrt) { this->aclrt = aclrt; }
	void SetEnd(bool bEnd) { this->bEnd = bEnd; }

private:
	shared_ptr<AnimationRect> animRect;
	
	float totalSize = 0.0f;

	float speed = 0.0f;
	float val = 0.0f;
	float jumpSpeed = 0.0f;
	float aclrt = 0.0f;

	bool bEnd = false;
	bool bActivation = false;
};

class SquidBulletManager
{
public:
	DECLARE_SINGLETON(SquidBulletManager);

public:
	void Collision(shared_ptr<Player> player);
	void Create();
	void Init(Vector2 position, float size, int currentFrame);

	void Update();
	void Render();

	void GUI();

public:
	vector<shared_ptr<SquidBullet>> GetSquidBulletList() { return squidBulletList; }

	void SetActivation(bool bActivation) { this->bActivation = bActivation; }

private:
	vector<shared_ptr<SquidBullet>> squidBulletList;
	mt19937 mt;

	Vector2 position = Vector2();
	float totalSize = 0.7f;
	Vector2 MSpeed = Vector2(-150.0f, 200.0f);
	Vector2 MJumpSpeed = Vector2(5.0f, 400.0f);
	float aclrt = 35.0f;

	float time = 0.0f;
	float delayTime = 0.2f;

	int currentIndex = 0;
	
	bool bActivation = false;
};
