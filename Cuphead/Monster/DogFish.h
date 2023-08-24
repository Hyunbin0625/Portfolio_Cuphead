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
	void Init(Vector2 position, float size);

	void Update();
	void Render();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	int GetState() { return (int)state; }
	float GetJumpSpeed() { return jumpSpeed; }
	float GetAclrt() { return aclrt; }
	
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }
	void SetSpeed(float speed) { this->speed = speed; }

	void SetJumpSpeed(float jumpSpeed) { this->jumpSpeed = jumpSpeed; }
	void SetAclrt(float aclrt) { this->aclrt = aclrt; }

private:
	shared_ptr<AnimationRect> animRect;
	shared_ptr<AnimationRect> dust;
	
	int hp = 0;
	UINT maxHp = 0;

	DogFishState state = DogFishState::None;
	Vector2 position = Vector2(0, 0);
	float totalSize = 0.1f;

	float speed = 605.0f;
	float jumpSpeed = 605.0f;
	float aclrt = 1.0f;

	int animCount = 0;
	bool bActivation = false;
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

private:
	vector<shared_ptr<DogFish>> dogFishList;
	shared_ptr<AnimationRect> animRect;
	mt19937 mt;

	Vector2 position = Vector2();
	float totalSize = 1.0f;
	float speed = 600.0f;

	float time = 0.0f;
	float delayTime = 10.0f;
	
	int count = 0;
	int currentIndex = 0;
	
	bool bActivation = false;
};
