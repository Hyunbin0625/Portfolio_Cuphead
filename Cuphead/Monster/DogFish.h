#pragma once

enum class DogFishState
{
	None,
	Up,
	Jump,
	Slide,
	Death
};

class DogFish
{
public:
	DogFish();

public:
	void Collision(shared_ptr<Player> player);
	void Init(Vector2 position, float size, float speed, int maxHp);

	void Update();
	void Render();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	int GetState() { return (int)state; }
	float GetMaxJumpSpeed() { return maxJumpSpeed; }
	float GetAclrt() { return aclrt; }
	
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }
	void SetSpeed(float speed) { this->speed = speed; }

	void SetMaxJumpSpeed(float maxJumpSpeed) { this->maxJumpSpeed = maxJumpSpeed; }
	void SetAclrt(float aclrt) { this->aclrt = aclrt; }
	void SetGround(float groundPosY) { this->groundPosY = groundPosY; }

private:
	shared_ptr<AnimationRect> animRect;
	shared_ptr<AnimationRect> dust;
	
	int hp = 0;
	DogFishState state = DogFishState::None;
	Vector2 position = Vector2(0, 0);
	float totalSize = 0.1f;

	float speed = 0.0f;
	float val = 0.0f;
	float jumpSpeed = 0.0f;
	float maxJumpSpeed = 1400.0f;
	float aclrt = 1000.0f;

	int animCount = 0;
	float groundPosY = 0.0f;
	bool bActivation = false;

	// Sounds
	bool bJumpS = false;
	bool bSlideS = false;
	bool bDeathS = false;
};

class DogFishManager
{
public:
	DECLARE_SINGLETON(DogFishManager);

public:
	void Collision(shared_ptr<Player> player);
	void Create();
	void Init(Vector2 position, float size);

	void Update();
	void Render();

	void GUI();

public:
	vector<shared_ptr<DogFish>> GetDogFishList() { return dogFishList; }

private:
	vector<shared_ptr<DogFish>> dogFishList;
	shared_ptr<AnimationRect> animRect;
	mt19937 mt;

	Vector2 position = Vector2();
	float totalSize = 1.0f;
	float speed = 450.0f;

	float time = 10.0f;
	float delayTime = 2.0f;
	
	int hp = 3;
	int count = 0;
	UINT maxCount = 0;
	int currentIndex = 0;
	
	bool bActivation = false;
};
