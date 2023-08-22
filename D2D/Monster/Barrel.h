#pragma once

enum class BarrelState
{
	Idle,
	Safe,
	Drop,
	Smash,
	Up
};

class Barrel
{
public:
	DECLARE_SINGLETON(Barrel);

public:
	void Collision(shared_ptr<Player> player);

	void Update();
	void Render();

	void GUI();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	bool GetDrop() { return bDrop; }

	void SetDrop(bool bDrop) { this->bDrop = bDrop; }
	void SetSmash(bool bSmash) { this->bSmash = bSmash; }
	
private:
	shared_ptr<AnimationRect> animRect;
	shared_ptr<AnimationRect> fx;
	shared_ptr<AnimationRect> dust;
	
	BarrelState state = BarrelState::Idle;
	Vector2 position = Vector2(1100, 680);
	float speed = 100.0f;
	float totalSize = 1.0f;

	float val = 0.0f;
	bool moveDrctn = false;
	bool animDrctn = false;
	float time = 0.0f;
	float safeTime = 4.0f;

	int animCount = 0;
	bool bDrop = false;
	bool bSmash = false;
	bool bUp = false;
	bool bSafe = false;
};
