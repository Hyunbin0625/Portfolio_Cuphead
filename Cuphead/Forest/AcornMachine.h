#pragma once

// run, Float, Down, jump
enum class AcornMachineState
{
	Idle,
	Create,
	Death
};

class AcornMachine : public IForestEnemy
{
public:	
	AcornMachine(const Vector2& position, float totailSize, float speed, int maxHp, bool bRegen, float regenTime, Direction direction);

public:
	virtual void Collision(shared_ptr<Player> player) override;
	virtual void Init() override;
	virtual void Destroy() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void GUI(int ordinal) override;

	virtual shared_ptr<AnimationRect> GetAnimRect() override { return animRect; }
	virtual shared_ptr<class LSeedManager> GetBullet() override { return nullptr; }

	virtual int GetHp()  override { return hp; }
	virtual bool GetDelete() override { return bDelete; }
	virtual ForestEnemyState GetState() override { return state; }

	virtual void SetState(ForestEnemyState state)  override { this->state = state; }
	virtual void SetHit(bool hit) override  { hp -= hit; }
	virtual void SetMod(bool mod) override  { this->bMod = mod; }
	virtual void SetWall(bool bWall) override {}
	virtual void SetGroundPos(Vector2 groundPos) override {}

private:
	shared_ptr<AnimationRect> animRect;
	shared_ptr<AnimationRect> animRect1;
	shared_ptr<AnimationRect> animRect2;
	shared_ptr<Acorn> acorn;

	// currentState
	ForestEnemyState state;
	AcornMachineState animState = AcornMachineState::Idle;
	Direction direction;

	int hp;

	bool check = false;

	bool bMod = 0;
	bool bDelete = 0;

	bool bDeathS = false;
};
