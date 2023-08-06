#pragma once

// run, Float, Down, jump
enum class AcornState
{
	Fly,
	Drop,
	DropLoop,
	Death
};

class Acorn : public IForestEnemy
{
public:	
	Acorn(const Vector2& position, float totailSize, float speed, int maxHp, bool bRegen, float regenTime, Direction direction);

public:
	virtual void Collision(shared_ptr<Player> player) override;
	virtual void Init() override;

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

public:
	float GetTime() { return time; }

	void SetAcornState(AcornState acornState) { this->animState = acornState; }
	void SetMachine(bool bMachine) { this->bMachine = bMachine; }
	void SetHp(int hp) { this->hp = hp; }

private:
	shared_ptr<AnimationRect> animRect;
	shared_ptr<AnimationRect> subAnimRect;

	// currentState
	ForestEnemyState state;
	AcornState animState = AcornState::Fly;
	Direction direction;

	int hp;
	float time = 0.0f;

	float playerX = 0.0f;
	bool bActivation = false;
	bool bMachine = false;

	bool bMod = 0;
	bool bDelete = 0;
};
