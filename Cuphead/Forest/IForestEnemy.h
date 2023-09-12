#pragma once

enum class ForestEnemyType
{
	None = -1,
	FlowerGrunt,
	Blob,
	Mushroom,
	Lobber,
	Chomper,
	Spiker,
	Acorn,
	AcornMachine,
};

#pragma pack(push, 1)
struct ForestEnemyState
{
	ForestEnemyType type = ForestEnemyType::None;

	Vector2 position = Vector2();
	float totalSize = 1;
	float speed = 0.0f;

	int maxHp = 0;

	bool bRegen = 0;
	float regenTime = 0;

	Direction direction = Direction::R;
};
#pragma pack(pop)

class IForestEnemy
{
public:
	IForestEnemy() = default;
	virtual ~IForestEnemy() = default;

public:
	virtual void Collision(shared_ptr<Player> player) = 0;
	virtual void Init() = 0;
	virtual void Destroy() = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void GUI(int ordinal) = 0;

	virtual shared_ptr<AnimationRect> GetAnimRect() = 0;
	virtual shared_ptr<class LSeedManager> GetBullet() = 0;
	virtual int GetHp() = 0;
	virtual bool GetDelete() = 0;
	virtual ForestEnemyState GetState() = 0;

	virtual void SetState(ForestEnemyState state) = 0;
	virtual void SetHit(bool hit) = 0;
	virtual void SetGroundPos(Vector2 groundPos) = 0;
	virtual void SetWall(bool bWall) = 0;
	virtual void SetMod(bool mod) = 0;
};
