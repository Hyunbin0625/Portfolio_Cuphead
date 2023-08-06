#pragma once

enum PlayerState
{
	None = 0,
	Idle_R,
	Idle_L,
	Run_R,
	Run_L,
	Jump_R,
	Jump_L,
	Parry_R,
	Parry_L,

	Down_R,
	Down_L,
	Shoot_Down_R,
	Shoot_Down_L,

	Shoot_R,
	Shoot_L,
	Run_Shoot_R,
	Run_Shoot_L,
	Run_Shoot_Diagonal_Up_R,
	Run_Shoot_Diagonal_Up_L,

	Aim_R,
	Aim_L,
	Aim_Diagonal_Up_R,
	Aim_Diagonal_Up_L,
	Aim_Diagonal_Down_R,
	Aim_Diagonal_Down_L,
	Aim_Up_R,
	Aim_Up_L,
	Aim_Down_R,
	Aim_Down_L,

	Aim_Shoot_Diagonal_Up_R,
	Aim_Shoot_Diagonal_Up_L,
	Aim_Shoot_Diagonal_Down_R,
	Aim_Shoot_Diagonal_Down_L,
	Aim_Shoot_Up_R,
	Aim_Shoot_Up_L,
	Aim_Shoot_Down_R,
	Aim_Shoot_Down_L,

	Dash,
	DashLoop,

	Special_Attack_R,
	Special_Attack_L,
	Special_Attack_Up_R,
	Special_Attack_Up_L,

	Air_Special_Attack_R,
	Air_Special_Attack_L,
	Air_Special_Attack_Up_R,
	Air_Special_Attack_Up_L,
	Air_Special_Attack_Down_R,
	Air_Special_Attack_Down_L,

	Super_Beam_R,
	Super_Beam_L,

	Hit_R,
	Hit_L,

	Death
};

enum Direction
{
	R = 0,
	L,
};

class Player
{
public:
	Player(const Vector2& position, const Vector2& scale, float speed, UINT hp, float maxSuperMeterCard);

public:
	void Move();
	void FDash();

public:
	void Update();
	void Render();

	void GUI();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	shared_ptr<PlayerBulletManager> GetBullet() { return bullet; }
	shared_ptr<PlayerSpecialAttackManager> GetSpecialAttack() { return specialAttack; }
	shared_ptr<SuperBeam> GetSuperBeam() { return superBeam; }

	PlayerState GetState() { return state; }
	Direction GetDirection() { return direction; }

	UINT GetHp() { return hp; }
	int GetSuperMeterCard() { return (int)superMeterCard; }
	int GetPercentSuperMeterCard() { return (int)(superMeterCard / maxSuperMeterCard * 100); }
	int GetMaxSuperMeterCard() { return (int)maxSuperMeterCard; }

	Vector2 GetPosition() { return position; }

	float GetTotalSize() const { return totalSize; }
	float GetSpeed() const { return speed; }
	float GetJumpSpeed() const { return jumpSpeed; }

	bool GetParry() { return bParry; }
	bool GetPlatform() { return platform; }
	bool GetMod() { return bMod; }

	void SetHp(int hp) { this->hp = hp; }
	void SetSuperMeterCard(float superMeterCard) { this->superMeterCard = superMeterCard; }
	void SetMaxSuperMeterCard(float maxSuperMeterCard) { this->maxSuperMeterCard = maxSuperMeterCard; }

	void SetPosition(Vector2 position) { this->position = position; }

	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }
	void SetJumpSpeed(float jumpSpeed) { this->jumpSpeed = jumpSpeed * totalSize; }

	void SetHit(bool hit) { if (!(state >= PlayerState::Special_Attack_R && state <= PlayerState::Death))this->hit = hit; }
	void SetGroundPos(Vector2 groundPos) { this->groundPos = groundPos; }
	void SetCheckCollider(bool checkCollider) { this->checkCollider = checkCollider; }
	void SetPlatform(bool platform) { this->platform = platform; }
	void SetG(float G) { this->G = G; }
	void SetMod(bool bMod) { this->bMod = bMod; }

private:
	UINT hp;
	UINT lastHp;

	bool hit = 0;
	float hitCTime = 0;
	
	float superMeterCard = 100;
	float maxSuperMeterCard;

	shared_ptr<AnimationRect> animRect;
	shared_ptr<PlayerBulletManager> bullet;
	shared_ptr<PlayerSpecialAttackManager> specialAttack;
	shared_ptr<SuperBeam> superBeam;
	unique_ptr<AnimationRect> SFXbullet;

	// start
	Vector2 position;
	Vector2 scale;

	// ground
	Vector2 groundPos;
	
	float totalSize = 1.0f;

	PlayerState state = PlayerState::Idle_R;
	Direction direction = Direction::R;
	float speed;

	float G = 0;
	float jumpSpeed = 0;
	float jumpMaxSpeed = 600;
	bool checkCollider = 0;
	UINT jumpCount = 2;

	bool bParry = 0;
	bool keyCheck = 0;

	float deltaTime = 0;
	int dash = 0;
	bool jumpDash = 0;

	int bSpecialAttack = 0;
	int bSuperBeam = 0;
	float maxTime = 3.0f;
	bool check = 0;

	bool platform = 0;

	float tempTime = 0;

	bool bMod = 0;
};
