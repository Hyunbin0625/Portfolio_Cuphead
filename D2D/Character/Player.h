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
};

enum Direction
{
	R = 0,
	L,
};

class Player
{
public:
	Player(const Vector2& position, const Vector2& scale, float speed);

public:
	void Move();
	void Jump();
	bool CheckGround(shared_ptr<ColorRect> ground);

public:
	void Init();
	void Destroy();

	void Update();
	void PreRender();
	void Render();
	void PostRender();

public:


private:
	unique_ptr<AnimationRect> animRect;
	shared_ptr<PlayerBullet> bullet;
	Vector2 position;
	Vector2 lastPos;
	Vector2 scale;

	State state = State::Idle_R;
	Direction direction = Direction::R;
	float speed;

	float G = 0;
	int speedG = 0;
	float jumpSpeed = 0;
	float jumpMaxSpeed = 500;
	bool checkCollider = 0;
	UINT jumpCount = 2;
};
