#pragma once

enum class ForestEnemyType
{
	None = -1,
	FlowerGrunt
};

struct ForestEnemyState
{
	ForestEnemyType type = ForestEnemyType::FlowerGrunt;

	Vector2 position;
	float totalSize = 1;
	float speed;

	int maxHp;

	bool bRegen = 0;
	float regenTime = 0;

	Direction direction = Direction::R;
};

class IForestEnemy
{
public:
	IForestEnemy() = default;
	virtual ~IForestEnemy() = default;

public:
	virtual void Collision(shared_ptr<Player> player) = 0;
	virtual void Init() = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void GUI(int ordinal) = 0;

	virtual shared_ptr<AnimationRect> GetAnimRect() = 0;
	virtual bool GetDelete() = 0;
	virtual ForestEnemyState GetState() = 0;

	virtual void SetState(ForestEnemyState state) = 0;
	virtual void SetHit(bool hit) = 0;
	virtual void SetGroundPos(Vector2 groundPos) = 0;
	virtual void SetWall(bool bWall) = 0;
	virtual void SetMod(bool mod) = 0;
};