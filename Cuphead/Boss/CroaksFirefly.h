#pragma once

enum class CroaksFireflyState
{
	Idle,
	Left,
	Right,
	Up,
	Down,
	Death
};

class CroaksFirefly
{
public:	
	CroaksFirefly(float speed);

public:
	void Collision(shared_ptr<Player> player);
	void Init(Vector2 position, Vector2 startPos);

	void Update();
	void Render();

	shared_ptr<AnimationRect> GetAnimRect()  { return animRect; }
	bool GetActivation() { return bActivation; }

	int GetHp() { return hp; }
	float GetSpeed() { return speed; }

	void SetActivation(bool bActivation) { this->bActivation = bActivation; }

	void SetHp(int hp) { this->hp = hp; }
	void SetSpeed(float speed) { this->speed = speed; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }

private:
	shared_ptr<AnimationRect> animRect;
	CroaksFireflyState animState = CroaksFireflyState::Idle;

	int hp = 1;
	float totalSize = 1.0f;
	float speed = 0.0f;

	float time = 0.0f;
	Vector2 dist = Vector2();
	bool bMove = false;

	Vector2 startPos = Vector2();
	Vector2 playerPos = Vector2();
	bool bActivation = false;

	// Sounds
	bool bDeathS = false;
};
