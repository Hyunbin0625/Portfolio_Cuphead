#pragma once

// run, Float, Down, jump
enum class LobberState
{
	Idle,
	Attack,
	Death
};

class Lobber : public IForestEnemy
{
public:	
	Lobber(const Vector2& position, float totailSize, float seedSpeed, int maxHp, bool bRegen, float regenTime, Direction direction);

public:
	virtual void Collision(shared_ptr<Player> player) override;
	virtual void Init() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void GUI(int ordinal) override;

	virtual shared_ptr<AnimationRect> GetAnimRect() override { return animRect; }
	virtual shared_ptr<class LSeedManager> GetBullet() override { return bullet; }
	virtual int GetHp()  override { return hp; }
	virtual bool GetDelete() override { return bDelete; }
	virtual ForestEnemyState GetState() override { return state; }

	virtual void SetState(ForestEnemyState state)  override { this->state = state; }
	virtual void SetHit(bool hit) override { hp -= hit; }
	virtual void SetMod(bool mod) override  { this->bMod = mod; }
	virtual void SetWall(bool bWall) override {}
	virtual void SetGroundPos(Vector2 groundPos) override { this->groundPos = groundPos; }

private:
	shared_ptr<AnimationRect> animRect;
	shared_ptr<class LSeedManager> bullet;

	ForestEnemyState state;

	LobberState animState = LobberState::Idle;

	float playerX = 0.0f;

	// currentState
	int hp;
	Direction direction;

	// ground
	Vector2 groundPos = Vector2(-1000, -1000);
	bool bGround = false;

	bool checkAttack = false;
	float time = 0.0f;

	int count = 0;

	bool bMod = 0;
	bool bDelete = 0;

	float distance = 0.0f;
	bool shoot = false;
};
