#pragma once

class Spiker : public IForestEnemy
{
public:	
	Spiker(const Vector2& position, float totailSize, float speed, int maxHp, bool bRegen, float range, Direction direction);

public:
	virtual void Collision(shared_ptr<Player> player) override;
	virtual void Init() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void GUI(int ordinal) override;

	virtual shared_ptr<AnimationRect> GetAnimRect() override { return animRect; }
	virtual bool GetDelete() override { return bDelete; }
	virtual ForestEnemyState GetState() override { return state; }

	virtual void SetState(ForestEnemyState state)  override { this->state = state; }
	virtual void SetMod(bool mod) override  { this->bMod = mod; }


	virtual shared_ptr<class LSeedManager> GetBullet() override { return nullptr; }
	virtual int GetHp() override { return 0; }

	virtual void SetHit(bool hit) override {}
	virtual void SetWall(bool bWall) override {}
	virtual void SetGroundPos(Vector2 groundPos) override {}

private:
	shared_ptr<AnimationRect> animRect;

	ForestEnemyState state;

	bool bMod = 0;
	bool bDelete = 0;

	bool bActivation;
	float parryTime;
};
