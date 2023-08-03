#pragma once

// run, Float, Down, jump
enum class MushroomState
{
	Idle,
	Attack,
	PopOut,
	PopIn,
	Death
};

class Mushroom : public IForestEnemy
{
public:	
	Mushroom(const Vector2& position, float totailSize, float poisonSpeed, int maxHp, bool bRegen, float regenTime, Direction direction);

public:
	virtual void Collision(shared_ptr<Player> player) override;
	virtual void Init() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void GUI(int ordinal) override;

	virtual shared_ptr<AnimationRect> GetAnimRect() override { return animRect; }
	virtual int GetHp()  override { return hp; }
	virtual bool GetDelete() override { return bDelete; }
	virtual ForestEnemyState GetState() override { return state; }

	virtual void SetState(ForestEnemyState state)  override { this->state = state; }
	virtual void SetHit(bool hit) override { if (animState != MushroomState::PopOut && animState != MushroomState::PopIn) hp -= hit; }
	virtual void SetMod(bool mod) override  { this->bMod = mod; }
	virtual void SetWall(bool bWall) override { this->bWall = bWall; }
	virtual void SetGroundPos(Vector2 groundPos) override { this->groundPos = groundPos; }

private:
	shared_ptr<AnimationRect> animRect;
	shared_ptr<class MRPoisonManager> bullet;

	ForestEnemyState state;
	bool playerDirection = 0;

	MushroomState animState = MushroomState::Idle;

	float theta = 0.0f;

	// currentState
	int hp;
	Direction direction;

	// ground
	Vector2 groundPos = Vector2(-1000, -1000);
	bool bGround = false;

	bool bWall = false;

	float time = 0.0f;
	float parryTime = 0.0f;

	bool bMod = 0;
	bool bDelete = 0;

	int checkState = 0;
	float distance = 0.0f;
	bool shoot = false;
};
