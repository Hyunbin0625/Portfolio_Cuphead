#pragma once

enum State
{
	None = 0,
	Idle_R,
	Idle_L,
	Run_R,
	Run_L,
	Jump_R,
	Jump_L,

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

	Dash_R,
	Dash_L,

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

public:
	void Update();
	void Render();

	void GUI();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	bool GetPlatform() { return platform; }
	UINT GetHp() { return hp; }
	int GetSuperMeterCard() { return superMeterCard / maxSuperMeterCard * 100; }

	void SetCheckCollider(bool checkCollider) { this->checkCollider = checkCollider; }
	void SetPlatform(bool platform) { this->platform = platform; }

private:
	UINT hp;
	UINT lastHp;
	
	float superMeterCard = 0;
	float maxSuperMeterCard;

	shared_ptr<AnimationRect> animRect;
	shared_ptr<PlayerBulletManager> bullet;
	shared_ptr<PlayerSpecialAttackManager> SpecialAttack;
	unique_ptr<AnimationRect> SFXbullet;

	Vector2 scale;
	
	Vector2 position;
	float totalSize = 1.0f;

	State state = State::Idle_R;
	Direction direction = Direction::R;
	float speed;

	float G = 0;
	float jumpSpeed = 0;
	float jumpMaxSpeed = 600;
	bool checkCollider = 0;
	UINT jumpCount = 2;

	float deltaTime = 0;
	int dash = 0;

	bool check = 0;
	bool specialAttack = 0;

	bool platform = 0;
};
