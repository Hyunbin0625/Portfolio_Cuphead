#include "stdafx.h"
#include "Player.h"

Player::Player(const Vector2& position, const Vector2& scale, float speed)
	: position(position), scale(scale), speed(speed)
{
	animRect = make_shared<AnimationRect>(position, scale, 0.0f, L"_Textures/Player/cuphead_idle_R.png");

	// Move
	// Idle
	animRect->AddAnimClip(make_shared<AnimationClip>(L"IdleR", L"_Textures/Player/cuphead_idle_R.png", 8, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"IdleL", L"_Textures/Player/cuphead_idle_L.png", 8, true, true, 0.1));
	// Run
	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunR", L"_Textures/Player/cuphead_run_R.png", 16, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunL", L"_Textures/Player/cuphead_run_L.png", 16, true, true, 0.1));

	// Jump
	animRect->AddAnimClip(make_shared<AnimationClip>(L"JumpR", L"_Textures/Player/cuphead_jump_R.png", 8, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"JumpL", L"_Textures/Player/cuphead_jump_L.png", 8, true, true, 0.1));

	// Shoot
	animRect->AddAnimClip(make_shared<AnimationClip>(L"ShootR", L"_Textures/Player/cuphead_shoot_straight.png", 6, false, true, 0.06));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"ShootL", L"_Textures/Player/cuphead_shoot_stleft.png", 6, true, true, 0.06));

	// Run_Shoot
	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunShootR", L"_Textures/Player/cuphead_run_shoot_R.png", 16, false, true, 0.09));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunShootL", L"_Textures/Player/cuphead_run_shoot_L.png", 16, true, true, 0.09));

	// Run_Shoot_Diagonal_Up
	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunShootDiagUpR", L"_Textures/Player/cuphead_run_shoot_diag_up_R.png", 16, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunShootDiagUpL", L"_Textures/Player/cuphead_run_shoot_diag_up_L.png", 16, true, true, 0.1));
	
	// Duck
	animRect->AddAnimClip(make_shared<AnimationClip>(L"DuckR", L"_Textures/Player/cuphead_duck_R.png", 10, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"DuckL", L"_Textures/Player/cuphead_duck_L.png", 10, true, true, 0.1));

	// Shoot_Duck
	animRect->AddAnimClip(make_shared<AnimationClip>(L"ShootDuckR", L"_Textures/Player/cuphead_duck_shoot_R.png", 3, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"ShootDuckL", L"_Textures/Player/cuphead_duck_shoot_L.png", 3, true, true, 0.1));

	// Aim
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimR", L"_Textures/Player/cuphead_aim_straight_R.png", 8, false, true, 0.105));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimL", L"_Textures/Player/cuphead_aim_straight_L.png", 8, true, true, 0.105));
	
	// Aim_Diagonal_Up
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimDiagUpR", L"_Textures/Player/cuphead_aim_diagonal_up_R.png", 8, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimDiagUpL", L"_Textures/Player/cuphead_aim_diagonal_up_L.png", 8, true, true, 0.1));

	// Aim_Diagonal_Down
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimDiagDownR", L"_Textures/Player/cuphead_aim_diagonal_down_R.png", 8, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimDiagDownL", L"_Textures/Player/cuphead_aim_diagonal_down_L.png", 8, true, true, 0.1));

	// Aim_Up
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimUpR", L"_Textures/Player/cuphead_aim_up_R.png", 8, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimUpL", L"_Textures/Player/cuphead_aim_up_L.png", 8, true, true, 0.1));

	// Aim_Down
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimDownR", L"_Textures/Player/cuphead_aim_down_R.png", 8, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimDownL", L"_Textures/Player/cuphead_aim_down_L.png", 8, true, true, 0.1));

	// Aim_Shoot_Diagonal_Up
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimShootDiagUpR", L"_Textures/Player/cuphead_shoot_diagonal_up_R.png", 6, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimShootDiagUpL", L"_Textures/Player/cuphead_shoot_diagonal_up_L.png", 6, true, true, 0.1));

	// Aim_Shoot_Diagonal_Down
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimShootDiagDownR", L"_Textures/Player/cuphead_shoot_diagonal_down_R.png", 6, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimShootDiagDownL", L"_Textures/Player/cuphead_shoot_diagonal_down_L.png", 6, true, true, 0.1));

	// Aim_Shoot_Up
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimShootUpR", L"_Textures/Player/cuphead_shoot_up_R.png", 6, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimShootUpL", L"_Textures/Player/cuphead_shoot_up_L.png", 6, true, true, 0.1));

	// Aim_Shoot_Down
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimShootDownR", L"_Textures/Player/cuphead_shoot_down_R.png", 6, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AimShootDownL", L"_Textures/Player/cuphead_shoot_down_L.png", 6, true, true, 0.1));

	// Dash
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Dash_R", L"_Textures/Player/cuphead_dash_R.png", 8, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Dash_L", L"_Textures/Player/cuphead_dash_L.png", 8, true, true, 0.1));
	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// Create Player Bullet
	bullet = make_shared<BulletManager>(10, 1500, 7);	// totalBullet, bulletSpeed, speakerSpeed

	SFXbullet = make_unique<AnimationRect>(Vector2(), Vector2(75, 69), 0.0f, L"_Textures/Player/weapon_peashot_spark.png");
	SFXbullet->AddAnimClip(make_shared<AnimationClip>(L"SFXBullet", L"_Textures/Player/weapon_peashot_spark.png", 4, false, true, 0.1));
	// AddAnimator
	SFXbullet->AddComponent(make_shared<AnimatorComponent>(SFXbullet->GetAnimClips()));
	// animRect SetAnimator
	SFXbullet->SetAnimator(SFXbullet->GET_COMP(Animator));

	// Components
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void Player::Move()
{
	if (!INPUT->Press('C') && !INPUT->Press(VK_DOWN) && !(runTime > 0.0f && runTime < 0.4f))
	{
		if (INPUT->Press(VK_LEFT))
			animRect->Move(Vector2(-speed, 0));
		if (INPUT->Press(VK_RIGHT))
			animRect->Move(Vector2(speed, 0));
	}

	if (INPUT->Down(VK_SHIFT) && runTime == 0.0f)
	{
		if (direction == Direction::L)
			animRect->Move(Vector2(-speed * 150, 0));
		else
			animRect->Move(Vector2(speed * 150, 0));
		dash = 1;
	}

	if (dash == 1)
		runTime += 1 * DELTA;

	if (runTime > 0.4f && dash == 1)
	{
		++dash;
		if (direction == Direction::L)
			animRect->Move(Vector2(-speed * 150, 0));
		else
			animRect->Move(Vector2(speed * 150, 0));
	}

	if (!INPUT->Press(VK_SHIFT) && runTime > 0.4f && dash == 2)
	{
		dash = 0;
		runTime = 0.0f;
	}
}

void Player::Update()
{
	if (platform == 1 && INPUT->Press(VK_DOWN) && INPUT->Press('Z'))
	{
		checkCollider = 0;
		++jumpCount;
	}	
	else if (INPUT->Down('Z') && checkCollider == 1)
	{
		++jumpCount;
		G = 0;
		jumpSpeed = jumpMaxSpeed;
		checkCollider = 0;
	}

	Move();
	if (checkCollider == 0)
	{
		G += 15 * DELTA;
		jumpSpeed -= G;

		animRect->Move(Vector2(0, jumpSpeed));

		if (jumpCount > 0)
		{
			if (direction == Direction::R)
				state = State::Jump_R;
			else
				state = State::Jump_L;

			if (INPUT->Press('X'))
			{
				if (INPUT->Press(VK_RIGHT) || direction == Direction::R)
				{
					direction = Direction::R;
					bullet->Init(Vector2(animRect->GetPosition().x + 60, animRect->GetPosition().y), 0.0f, 0.0f);
				}

				if (INPUT->Press(VK_LEFT) || direction == Direction::L)
				{
					direction = Direction::L;
					bullet->Init(Vector2(animRect->GetPosition().x - 60, animRect->GetPosition().y), 180.0f, 0.0f);
				}

				if (INPUT->Press(VK_UP))
					bullet->Init(Vector2(animRect->GetPosition().x, animRect->GetPosition().y + 80), -90.0f, 0.0f);

				if (INPUT->Press(VK_DOWN))
					bullet->Init(Vector2(animRect->GetPosition().x, animRect->GetPosition().y - 80), 90.0f, 0.0f);

				if (INPUT->Press(VK_RIGHT) && INPUT->Press(VK_UP))
					bullet->Init(Vector2(animRect->GetPosition().x + 60, animRect->GetPosition().y + 60), -45.0f, 21.0f);

				if (INPUT->Press(VK_LEFT) && INPUT->Press(VK_UP))
					bullet->Init(Vector2(animRect->GetPosition().x - 60, animRect->GetPosition().y + 60), -135.0f, 21.0f);

				if (INPUT->Press(VK_RIGHT) && INPUT->Press(VK_DOWN))
					bullet->Init(Vector2(animRect->GetPosition().x + 60, animRect->GetPosition().y - 60), 45.0f, 21.0f);

				if (INPUT->Press(VK_LEFT) && INPUT->Press(VK_DOWN))
					bullet->Init(Vector2(animRect->GetPosition().x - 60, animRect->GetPosition().y - 60), 135.0f, 21.0f);
			}
		}
	}
	else
	{
		jumpCount = 0;
		G = 0;

		// Idle
		if (direction == Direction::R)
			state = State::Idle_R;
		else
			state = State::Idle_L;

		// 조준
		if (INPUT->Press('C'))
		{
			// 조준 + Shoot
			if (INPUT->Press('X'))
			{
				if (INPUT->Press(VK_RIGHT))
				{
					state = State::Shoot_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT))
				{
					state = State::Shoot_L;
					direction = Direction::L;
				}

				if (INPUT->Press(VK_UP))
				{
					if (direction == Direction::R)
						state = State::Aim_Shoot_Up_R;
					else
						state = State::Aim_Shoot_Up_L;
				}
					
				if (INPUT->Press(VK_DOWN))
				{
					if (direction == Direction::R)
						state = State::Aim_Shoot_Down_R;
					else
						state = State::Aim_Shoot_Down_L;
				}
					
				if (INPUT->Press(VK_RIGHT) && INPUT->Press(VK_UP))
				{
					state = State::Aim_Shoot_Diagonal_Up_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT) && INPUT->Press(VK_UP))
				{
					state = State::Aim_Shoot_Diagonal_Up_L;
					direction = Direction::L;
				}

				if (INPUT->Press(VK_RIGHT) && INPUT->Press(VK_DOWN))
				{
					state = State::Aim_Shoot_Diagonal_Down_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT) && INPUT->Press(VK_DOWN))
				{
					state = State::Aim_Shoot_Diagonal_Down_L;
					direction = Direction::L;
				}
			}
			else	// 조준
			{
				if (INPUT->Press(VK_RIGHT))
				{
					state = State::Aim_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT))
				{
					state = State::Aim_L;
					direction = Direction::L;
				}

				if (INPUT->Press(VK_UP))
				{
					if (direction == Direction::R)
						state = State::Aim_Up_R;
					else
						state = State::Aim_Up_L;
				}

				if (INPUT->Press(VK_DOWN))
				{
					if (direction == Direction::R)
						state = State::Aim_Down_R;
					else
						state = State::Aim_Down_L;
				}	

				if (INPUT->Press(VK_RIGHT) && INPUT->Press(VK_UP))
				{
					state = State::Aim_Diagonal_Up_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT) && INPUT->Press(VK_UP))
				{
					state = State::Aim_Diagonal_Up_L;
					direction = Direction::L;
				}

				if (INPUT->Press(VK_RIGHT) && INPUT->Press(VK_DOWN))
				{
					state = State::Aim_Diagonal_Down_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT) && INPUT->Press(VK_DOWN))
				{
					state = State::Aim_Diagonal_Down_L;
					direction = Direction::L;
				}
			}
		}
		else	// 이동
		{
			// 이동 + Shoot
			if (INPUT->Press('X'))
			{
				if (direction == Direction::R)
				{
					state = State::Shoot_R;
				}

				if (direction == Direction::L)
				{
					state = State::Shoot_L;
				}

				if (INPUT->Press(VK_RIGHT))
				{
					state = State::Run_Shoot_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT))
				{
					state = State::Run_Shoot_L;
					direction = Direction::L;
				}

				if (INPUT->Press(VK_UP) && direction == Direction::R)
				{
					state = State::Aim_Shoot_Up_R;
				}

				if (INPUT->Press(VK_UP) && direction == Direction::L)
				{
					state = State::Aim_Shoot_Up_L;
				}

				if (INPUT->Press(VK_RIGHT) && INPUT->Press(VK_UP))
				{
					state = State::Run_Shoot_Diagonal_Up_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT) && INPUT->Press(VK_UP))
				{
					state = State::Run_Shoot_Diagonal_Up_L;
					direction = Direction::L;
				}

				if (INPUT->Press(VK_DOWN))
				{
					if (INPUT->Press(VK_RIGHT) || direction == Direction::R)
					{
						state = State::Shoot_Down_R;
						direction = Direction::R;
					}
					else if (INPUT->Press(VK_LEFT) || direction == Direction::L)
					{
						state = State::Shoot_Down_L;
						direction = Direction::L;
					}
				}
			}
			else	// 이동
			{
				if (INPUT->Press(VK_RIGHT))
				{
					state = State::Run_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT))
				{
					state = State::Run_L;
					direction = Direction::L;
				}

				if (INPUT->Press(VK_UP))
				{
					if (direction == Direction::R)
						state = State::Aim_Up_R;
					else
						state = State::Aim_Up_L;
				}

				if (INPUT->Press(VK_RIGHT) && INPUT->Press(VK_UP))
				{
					state = State::Run_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT) && INPUT->Press(VK_UP))
				{
					state = State::Run_L;
					direction = Direction::L;
				}

				if (INPUT->Press(VK_DOWN))
				{
					if (direction == Direction::R)
						state = State::Down_R;
					else
						state = State::Down_L;
				}
			}
		}
	}

	if (dash >= 1 && runTime > 0.0f && runTime < 0.4f)
	{
		cout << runTime << '\n';
		jumpSpeed = 0;
		if (direction == Direction::R)
			state = State::Dash_R;
		else
			state = State::Dash_L;
	}
	
	if (scale != animRect->GetScale())
		animRect->SetScale(scale * scaleSize);
	SFXbullet->SetPosition(Vector2(-1000, -1000));

	switch (state)
	{
	case Idle_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"IdleR");
		break;
	case Idle_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"IdleL");
		break;
	case Run_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunR");
		animRect->SetScale(Vector2(137, 169)* scaleSize);
		break;
	case Run_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunL");
		animRect->SetScale(Vector2(137, 169)* scaleSize);
		break;
	case Jump_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"JumpR");
		animRect->SetScale(Vector2(88, 109)* scaleSize);
		break;
	case Jump_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"JumpL");
		animRect->SetScale(Vector2(88, 109)* scaleSize);
		break;
	case Down_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"DuckR");
		animRect->SetScale(Vector2(168, 92)* scaleSize);	// Duck_size	나중에 매크로로 저장
		break;
	case Down_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"DuckL");
		animRect->SetScale(Vector2(168, 92)* scaleSize);
		break;
	case Shoot_Down_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"ShootDuckR");
		animRect->SetScale(Vector2(178, 81)* scaleSize);
		bullet->Init(Vector2(animRect->GetPosition().x + 100, animRect->GetPosition().y), 0.0f, 21.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 80, animRect->GetPosition().y));
		break;
	case Shoot_Down_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"ShootDuckL");
		animRect->SetScale(Vector2(178, 81)* scaleSize);
		bullet->Init(Vector2(animRect->GetPosition().x - 100, animRect->GetPosition().y), 180.0f, 21.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 80, animRect->GetPosition().y));
		break;
	case Shoot_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"ShootR");
		animRect->SetScale(Vector2(127, 155)* scaleSize);
		bullet->Init(Vector2(animRect->GetPosition().x + 75, animRect->GetPosition().y + 5), 0.0f, 43.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 55, animRect->GetPosition().y + 5));
		break;
	case Shoot_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"ShootL");
		animRect->SetScale(Vector2(127, 155)* scaleSize);
		bullet->Init(Vector2(animRect->GetPosition().x - 75, animRect->GetPosition().y + 5), -180.0f, 43.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 55, animRect->GetPosition().y + 5));
		break;
	case Run_Shoot_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunShootR");
		animRect->SetScale(Vector2(144, 162)* scaleSize);
		bullet->Init(Vector2(animRect->GetPosition().x + 75, animRect->GetPosition().y - 10), 0.0f, 43.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 55, animRect->GetPosition().y - 10));
		break;
	case Run_Shoot_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunShootL");
		animRect->SetScale(Vector2(144, 162)* scaleSize);
		bullet->Init(Vector2(animRect->GetPosition().x - 75, animRect->GetPosition().y - 10), -180.0f, 43.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 55, animRect->GetPosition().y - 10));
		break;
	case Run_Shoot_Diagonal_Up_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunShootDiagUpR");
		animRect->SetScale(Vector2(143, 157)* scaleSize);
		bullet->Init(Vector2(animRect->GetPosition().x + 75, animRect->GetPosition().y + 65), -45.0f, 10.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 55, animRect->GetPosition().y + 45));
		break;
	case Run_Shoot_Diagonal_Up_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunShootDiagUpL");
		animRect->SetScale(Vector2(143, 157)* scaleSize);
		bullet->Init(Vector2(animRect->GetPosition().x - 75, animRect->GetPosition().y + 65), -135.0f, 10.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 55, animRect->GetPosition().y + 45));
		break;
	case Aim_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimR");
		animRect->SetScale(Vector2(135, 161)* scaleSize);
		break;
	case Aim_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimL");
		animRect->SetScale(Vector2(135, 161) * scaleSize);
		break;
	case Aim_Diagonal_Up_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimDiagUpR");
		animRect->SetScale(Vector2(129, 151)* scaleSize);
		break;
	case Aim_Diagonal_Up_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimDiagUpL");
		animRect->SetScale(Vector2(129, 151)* scaleSize);
		break;
	case Aim_Diagonal_Down_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimDiagDownR");
		animRect->SetScale(Vector2(118, 163) * scaleSize);
		break;
	case Aim_Diagonal_Down_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimDiagDownL");
		animRect->SetScale(Vector2(118, 163) * scaleSize);
		break;
	case Aim_Up_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimUpR");
		animRect->SetScale(Vector2(108, 175) * scaleSize);
		break;
	case Aim_Up_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimUpL");
		animRect->SetScale(Vector2(108, 175) * scaleSize);
		break;
	case Aim_Down_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimDownR");
		animRect->SetScale(Vector2(103, 168) * scaleSize);
		break;
	case Aim_Down_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimDownL");
		animRect->SetScale(Vector2(103, 168) * scaleSize);
		break;
	case Aim_Shoot_Diagonal_Up_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimShootDiagUpR");
		animRect->SetScale(Vector2(130, 154) * scaleSize);
		bullet->Init(Vector2(animRect->GetPosition().x + 75, animRect->GetPosition().y + 65), -45.0f, 10.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 55, animRect->GetPosition().y + 45));
		break;
	case Aim_Shoot_Diagonal_Up_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimShootDiagUpL");
		animRect->SetScale(Vector2(130, 154) * scaleSize);
		bullet->Init(Vector2(animRect->GetPosition().x - 75, animRect->GetPosition().y + 65), -135.0f, 10.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 55, animRect->GetPosition().y + 45));
		break;
	case Aim_Shoot_Diagonal_Down_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimShootDiagDownR");
		animRect->SetScale(Vector2(120, 163) * scaleSize);
		bullet->Init(Vector2(animRect->GetPosition().x + 75, animRect->GetPosition().y - 65), 45.0f, 10.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 55, animRect->GetPosition().y - 45));
		break;
	case Aim_Shoot_Diagonal_Down_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimShootDiagDownL");
		animRect->SetScale(Vector2(120, 163) * scaleSize);
		bullet->Init(Vector2(animRect->GetPosition().x - 75, animRect->GetPosition().y - 65), 135.0f, 10.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 55, animRect->GetPosition().y - 45));
		break;
	case Aim_Shoot_Up_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimShootUpR");
		animRect->SetScale(Vector2(108, 179) * scaleSize);
		bullet->Init(Vector2(animRect->GetPosition().x + 30, animRect->GetPosition().y + 110), -90.0f, 0.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 30, animRect->GetPosition().y + 85));
		break;
	case Aim_Shoot_Up_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimShootUpL");
		animRect->SetScale(Vector2(108, 179) * scaleSize);
		bullet->Init(Vector2(animRect->GetPosition().x - 30, animRect->GetPosition().y + 110), -90.0f, 0.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 30, animRect->GetPosition().y + 85));
		break;
	case Aim_Shoot_Down_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimShootDownR");
		animRect->SetScale(Vector2(102, 171) * scaleSize);
		bullet->Init(Vector2(animRect->GetPosition().x + 30, animRect->GetPosition().y - 110), 90.0f, 0.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 30, animRect->GetPosition().y - 85));
		break;
	case Aim_Shoot_Down_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimShootDownL");
		animRect->SetScale(Vector2(102, 171) * scaleSize);
		bullet->Init(Vector2(animRect->GetPosition().x - 30, animRect->GetPosition().y - 110), 90.0f, 0.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 30, animRect->GetPosition().y - 85));
		break;
	case Dash_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Dash_R");
		animRect->SetScale(Vector2(326, 163) * scaleSize);
		break;
	case Dash_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Dash_L");
		animRect->SetScale(Vector2(326, 163) * scaleSize);
		break;
	}

	if (INPUT->Press('X'))
	{
		bullet->SetTime(bullet->GetTime() + bullet->GetSpeakerSpeed() * DELTA);
		if ((int)bullet->GetTime() != bullet->GetLastIndex())
		{
			bullet->SetLastIndex((int)bullet->GetTime());
			bullet->SetActivation((int)bullet->GetTime(), 1);
			bullet->SetNextIndex(bullet->GetNextIndex() + 1);
		}
	}
	else
		bullet->SetTime(bullet->GetLastIndex() + 1);

	SFXbullet->Update();
	animRect->Update();
	bullet->Update();
}

void Player::Render()
{
	SFXbullet->Render();
	animRect->Render();
	bullet->Render();
}

void Player::GUI()
{
	static bool bOpen = true;
	if (ImGui::Begin("Player", &bOpen))
	{
		ImGui::SliderFloat("Scale", &scaleSize, 0.0f, 2.0f, "%.2f");
	}
	ImGui::End();
}
