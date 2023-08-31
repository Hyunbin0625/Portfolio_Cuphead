#include "stdafx.h"
#include "Player.h"

Player::Player(const Vector2& position, const Vector2& scale, float speed, UINT hp, float maxSuperMeterCard)
	: position(position), scale(scale), speed(speed), hp(hp), maxSuperMeterCard(maxSuperMeterCard)
{
	lastHp = hp;
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

	// Parry
	animRect->AddAnimClip(make_shared<AnimationClip>(L"ParryR", L"_Textures/Player/cuphead_parry_R.png", 8, false, false, 0.06));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"ParryL", L"_Textures/Player/cuphead_parry_L.png", 8, true, false, 0.06));

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
	animRect->AddAnimClip(make_shared<AnimationClip>(L"DashR", L"_Textures/Player/cuphead_dash_pre_R.png", 2, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"DashL", L"_Textures/Player/cuphead_dash_pre_L.png", 2, true, false, 0.1));

	// DashLoop
	animRect->AddAnimClip(make_shared<AnimationClip>(L"DashLoopR", L"_Textures/Player/cuphead_dash_R.png", 6, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"DashLoopL", L"_Textures/Player/cuphead_dash_L.png", 6, true, true, 0.1));

	// Ground_Special_Attack
	animRect->AddAnimClip(make_shared<AnimationClip>(L"SpecialAttackR", L"_Textures/Player/cuphead_ex_straight_R.png", 15, false, false, 0.11));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"SpecialAttackL", L"_Textures/Player/cuphead_ex_straight_L.png", 15, true, false, 0.11));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"SpecialAttackUpR", L"_Textures/Player/cuphead_ex_up_R.png", 15, false, false, 0.11));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"SpecialAttackUpL", L"_Textures/Player/cuphead_ex_up_L.png", 15, true, false, 0.11));

	// Air_Special_Attack
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AirSpecialAttackR", L"_Textures/Player/cuphead_ex_straight_air_R.png", 15, false, false, 0.11));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AirSpecialAttackL", L"_Textures/Player/cuphead_ex_straight_air_L.png", 15, true, false, 0.11));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AirSpecialAttackUpR", L"_Textures/Player/cuphead_ex_up_air_R.png", 15, false, false, 0.11));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AirSpecialAttackUpL", L"_Textures/Player/cuphead_ex_up_air_L.png", 15, true, false, 0.11));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AirSpecialAttackDownR", L"_Textures/Player/cuphead_ex_down_air_R.png", 15, false, false, 0.11));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AirSpecialAttackDownL", L"_Textures/Player/cuphead_ex_down_air_L.png", 15, true, false, 0.11));
	
	// Super_Beam
	animRect->AddAnimClip(make_shared<AnimationClip>(L"SuperBeamIntroR1", L"_Textures/Player/cuphead_super_beam_intro_R_01.png", 13, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"SuperBeamIntroL1", L"_Textures/Player/cuphead_super_beam_intro_L_01.png", 13, true, false, 0.1));

	// 0.3초 대기 후 실행
	animRect->AddAnimClip(make_shared<AnimationClip>(L"SuperBeamIntroR2", L"_Textures/Player/cuphead_super_beam_intro_R_02.png", 7, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"SuperBeamIntroL2", L"_Textures/Player/cuphead_super_beam_intro_L_02.png", 7, true, false, 0.1));
	
	// 2초 정도 loop
	animRect->AddAnimClip(make_shared<AnimationClip>(L"SuperBeamLoopR", L"_Textures/Player/cuphead_super_beam_loop_R.png", 3, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"SuperBeamLoopL", L"_Textures/Player/cuphead_super_beam_loop_L.png", 3, true, true, 0.1));

	// Hit
	animRect->AddAnimClip(make_shared<AnimationClip>(L"HitR", L"_Textures/Player/cuphead_hit_air_R.png", 6, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"HitL", L"_Textures/Player/cuphead_hit_air_L.png", 6, true, false, 0.1));

	// Death
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Death", L"_Textures/Player/cuphead_death_body.png", 16, false, false, 0.1));

	// Intro
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Intro", L"_Textures/Player/cuphead_intro_a.png", 28, false, false, 0.1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// Create Player Bullet
	bullet = make_shared<PlayerBulletManager>(10, 1500, 7);	// totalBullet, bulletSpeed, speakerSpeed

	// Create Special Attack
	specialAttack = make_shared<PlayerSpecialAttackManager>(1, 800);	// totalBullet, bulletSpeed, speakerSpeed

	// Create Special Attack
	superBeam = make_shared<SuperBeam>();

	SFXbullet = make_unique<AnimationRect>(Vector2(), Vector2(75, 69), 0.0f, L"_Textures/SFX/weapon_peashot_spark.png");
	SFXbullet->AddAnimClip(make_shared<AnimationClip>(L"SFXBullet", L"_Textures/SFX/weapon_peashot_spark.png", 4, false, true, 0.1));
	// AddAnimator
	SFXbullet->AddComponent(make_shared<AnimatorComponent>(SFXbullet->GetAnimClips()));
	// animRect SetAnimator
	SFXbullet->SetAnimator(SFXbullet->GET_COMP(Animator));

	// Components
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));

	// Sound
	SOUND->AddSound("Shoot", L"_Sounds/sfx_player_default_fire_loop_01.wav", true);
	SOUND->AddSound("Dash", L"_Sounds/sfx_player_dash_01.wav", false);
	SOUND->AddSound("Crack", L"_Sounds/sfx_player_damage_crack_level3.wav", false);
	SOUND->AddSound("Hit", L"_Sounds/sfx_player_hit_01.wav", false);
	SOUND->AddSound("Death", L"_Sounds/sfx_player_death_01.wav", false);
	SOUND->AddSound("Jump", L"_Sounds/sfx_player_jump_01.wav", false);
	SOUND->AddSound("BeamS", L"_Sounds/sfx_player_super_beam_start_01.wav", false);
	SOUND->AddSound("BeamL", L"_Sounds/sfx_player_super_beam_firing_loop.wav", false);
}

void Player::Move()
{
	if (!INPUT->Press('C') && !INPUT->Press(VK_DOWN) && (dash == 0 || dash == 3))
	{
		if (INPUT->Press(VK_LEFT) && (animRect->GetPosition().x - animRect->GetScale().x * 0.5f) > CAMERA->GetPosition().x)
			animRect->Move(Vector2(-speed, 0) * totalSize);
		if (INPUT->Press(VK_RIGHT) && (animRect->GetPosition().x + animRect->GetScale().x * 0.5f) < CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH)
			animRect->Move(Vector2(speed, 0) * totalSize);
	}
}

void Player::FDash()
{
	if (INPUT->Down(VK_SHIFT) && dash == 0 && deltaTime == 0.0f && jumpDash)
	{
		dash = 1;
		jumpDash = false;
	}

	if (dash >= 2)
		deltaTime += 1 * DELTA;

	if (deltaTime > 0.4f && dash == 2)
		dash = 3;

	if (!INPUT->Press(VK_SHIFT) && deltaTime > 0.6f && dash == 3)
	{
		dash = 0;
		deltaTime = 0.0f;
	}
}

void Player::Update()
{
	if (bMod)
	{
		if (!(ImGui::IsAnyItemActive()) && animRect->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			position = INPUT->GetMousePosition();
		animRect->SetPosition(position);
		bIntro = true;
	}

	// Hit
	if (hit && hitCTime <= 0.0f)
	{
		hitCTime = 2.0f;
		hp -= hit;
		hit = 0;
	}

	if (hitCTime >= 0.0f)
	{
		hitCTime -= 1 * DELTA;
		hit = 0;
	}

	// SFX Init
	SFXbullet->SetPosition(Vector2(-1000, -1000));
	SFXbullet->SetScale(Vector2(75, 69) * totalSize);

	// Down Platform or Jump
	if (state != PlayerState::Death && bSpecialAttack == 0 && bSuperBeam == 0 && !bMod)
	{
		if (platform == 1 && INPUT->Press(VK_DOWN) && INPUT->Press('Z'))
		{
			checkCollider = 0;
			++jumpCount;
		}
		else if (INPUT->Down('Z') && checkCollider == 1)
		{
			++jumpCount;
			vel = 0;
			jumpSpeed = jumpMaxSpeed;
			checkCollider = 0;
		}

		Move();
		FDash();
	}

	// Air or Ground
	if (checkCollider == 0 && bSpecialAttack == 0 && bSuperBeam == 0 && !bMod && !bIntro)
	{
		vel += (float)(G * 700 * DELTA);
		jumpSpeed -= vel * DELTA;

		animRect->Move(Vector2(0, jumpSpeed) * totalSize);

		// Jump state
		if (jumpCount == 1 || (jumpCount == 0 && jumpSpeed < -5.0f))	// 보류
		{
			if (INPUT->Press(VK_RIGHT) || direction == Direction::R)
			{
				direction = Direction::R;
				state = PlayerState::Jump_R;
			}
			if (INPUT->Press(VK_LEFT) || direction == Direction::L)
			{
				direction = Direction::L;
				state = PlayerState::Jump_L;
			}
		}

		// Parry Slap
		if (!INPUT->Press('Z') && !INPUT->Down('Z') && INPUT->Up('Z') && jumpCount == 1 && animRect->GetPosition().y >= groundPos.y + 200)
		{
			keyCheck = true;
		}

		bParry = 0;
		if (INPUT->Press('Z') && keyCheck)
		{
			bParry = true;
			if (INPUT->Press(VK_RIGHT) || direction == Direction::R)
			{
				direction = Direction::R;
				state = PlayerState::Parry_R;
			}
			else if (INPUT->Press(VK_LEFT) || direction == Direction::L)
			{
				direction = Direction::L;
				state = PlayerState::Parry_L;
			}
		}

		if (INPUT->Press('X') && state != PlayerState::Death && bSpecialAttack != 1 && bSuperBeam != 1)
		{
			if (INPUT->Press(VK_RIGHT) || direction == Direction::R)
			{
				direction = Direction::R;
				bullet->Init(Vector2(animRect->GetPosition().x + 60 * totalSize, animRect->GetPosition().y), 0.0f, 0.0f);
				SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 60 * totalSize, animRect->GetPosition().y));
			}

			if (INPUT->Press(VK_LEFT) || direction == Direction::L)
			{
				direction = Direction::L;
				bullet->Init(Vector2(animRect->GetPosition().x - 60 * totalSize, animRect->GetPosition().y), 180.0f, 0.0f);
				SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 60 * totalSize, animRect->GetPosition().y));
			}

			if (INPUT->Press(VK_UP))
			{
				bullet->Init(Vector2(animRect->GetPosition().x, animRect->GetPosition().y + 80 * totalSize), -90.0f, 0.0f);
				SFXbullet->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y + 80 * totalSize));
			}

			if (INPUT->Press(VK_DOWN))
			{
				bullet->Init(Vector2(animRect->GetPosition().x, animRect->GetPosition().y - 80 * totalSize), 90.0f, 0.0f);
				SFXbullet->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y - 80 * totalSize));
			}

			if (INPUT->Press(VK_RIGHT) && INPUT->Press(VK_UP))
			{
				bullet->Init(Vector2(animRect->GetPosition().x + 60 * totalSize, animRect->GetPosition().y + 60 * totalSize), -45.0f, 21.0f);
				SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 60 * totalSize, animRect->GetPosition().y + 60 * totalSize));
			}

			if (INPUT->Press(VK_LEFT) && INPUT->Press(VK_UP))
			{
				bullet->Init(Vector2(animRect->GetPosition().x - 60 * totalSize, animRect->GetPosition().y + 60 * totalSize), -135.0f, 21.0f);
				SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 60 * totalSize, animRect->GetPosition().y + 60 * totalSize));
			}

			if (INPUT->Press(VK_RIGHT) && INPUT->Press(VK_DOWN))
			{
				bullet->Init(Vector2(animRect->GetPosition().x + 60 * totalSize, animRect->GetPosition().y - 60 * totalSize), 45.0f, 21.0f);
				SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 60 * totalSize, animRect->GetPosition().y - 60 * totalSize));
			}

			if (INPUT->Press(VK_LEFT) && INPUT->Press(VK_DOWN))
			{
				bullet->Init(Vector2(animRect->GetPosition().x - 60 * totalSize, animRect->GetPosition().y - 60 * totalSize), 135.0f, 21.0f);
				SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 60 * totalSize, animRect->GetPosition().y - 60 * totalSize));
			}
		}
	}
	else if(bSpecialAttack == 0 && bSuperBeam == 0)
	{
		jumpDash = true;
		jumpSpeed = 0;
		jumpCount = 0;
		vel = 0;

		// Idle
		if (direction == Direction::R)
			state = PlayerState::Idle_R;
		else
			state = PlayerState::Idle_L;

		// 조준
		if (INPUT->Press('C'))
		{
			// 조준 + Shoot
			if (INPUT->Press('X'))
			{
				if (INPUT->Press(VK_RIGHT))
				{
					state = PlayerState::Shoot_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT))
				{
					state = PlayerState::Shoot_L;
					direction = Direction::L;
				}

				if (INPUT->Press(VK_UP))
				{
					if (direction == Direction::R)
						state = PlayerState::Aim_Shoot_Up_R;
					else
						state = PlayerState::Aim_Shoot_Up_L;
				}
					
				if (INPUT->Press(VK_DOWN))
				{
					if (direction == Direction::R)
						state = PlayerState::Aim_Shoot_Down_R;
					else
						state = PlayerState::Aim_Shoot_Down_L;
				}
					
				if (INPUT->Press(VK_RIGHT) && INPUT->Press(VK_UP))
				{
					state = PlayerState::Aim_Shoot_Diagonal_Up_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT) && INPUT->Press(VK_UP))
				{
					state = PlayerState::Aim_Shoot_Diagonal_Up_L;
					direction = Direction::L;
				}

				if (INPUT->Press(VK_RIGHT) && INPUT->Press(VK_DOWN))
				{
					state = PlayerState::Aim_Shoot_Diagonal_Down_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT) && INPUT->Press(VK_DOWN))
				{
					state = PlayerState::Aim_Shoot_Diagonal_Down_L;
					direction = Direction::L;
				}
			}
			else	// 조준
			{
				if (INPUT->Press(VK_RIGHT))
				{
					state = PlayerState::Aim_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT))
				{
					state = PlayerState::Aim_L;
					direction = Direction::L;
				}

				if (INPUT->Press(VK_UP))
				{
					if (direction == Direction::R)
						state = PlayerState::Aim_Up_R;
					else
						state = PlayerState::Aim_Up_L;
				}

				if (INPUT->Press(VK_DOWN))
				{
					if (direction == Direction::R)
						state = PlayerState::Aim_Down_R;
					else
						state = PlayerState::Aim_Down_L;
				}	

				if (INPUT->Press(VK_RIGHT) && INPUT->Press(VK_UP))
				{
					state = PlayerState::Aim_Diagonal_Up_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT) && INPUT->Press(VK_UP))
				{
					state = PlayerState::Aim_Diagonal_Up_L;
					direction = Direction::L;
				}

				if (INPUT->Press(VK_RIGHT) && INPUT->Press(VK_DOWN))
				{
					state = PlayerState::Aim_Diagonal_Down_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT) && INPUT->Press(VK_DOWN))
				{
					state = PlayerState::Aim_Diagonal_Down_L;
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
					state = PlayerState::Shoot_R;
				}

				if (direction == Direction::L)
				{
					state = PlayerState::Shoot_L;
				}

				if (INPUT->Press(VK_RIGHT))
				{
					state = PlayerState::Run_Shoot_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT))
				{
					state = PlayerState::Run_Shoot_L;
					direction = Direction::L;
				}

				if (INPUT->Press(VK_UP) && direction == Direction::R)
				{
					state = PlayerState::Aim_Shoot_Up_R;
				}

				if (INPUT->Press(VK_UP) && direction == Direction::L)
				{
					state = PlayerState::Aim_Shoot_Up_L;
				}

				if (INPUT->Press(VK_RIGHT) && INPUT->Press(VK_UP))
				{
					state = PlayerState::Run_Shoot_Diagonal_Up_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT) && INPUT->Press(VK_UP))
				{
					state = PlayerState::Run_Shoot_Diagonal_Up_L;
					direction = Direction::L;
				}

				if (INPUT->Press(VK_DOWN))
				{
					if (INPUT->Press(VK_RIGHT) || direction == Direction::R)
					{
						state = PlayerState::Shoot_Down_R;
						direction = Direction::R;
					}
					else if (INPUT->Press(VK_LEFT) || direction == Direction::L)
					{
						state = PlayerState::Shoot_Down_L;
						direction = Direction::L;
					}
				}
			}
			else	// 이동
			{
				if (INPUT->Press(VK_RIGHT))
				{
					state = PlayerState::Run_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT))
				{
					state = PlayerState::Run_L;
					direction = Direction::L;
				}

				if (INPUT->Press(VK_UP))
				{
					if (direction == Direction::R)
						state = PlayerState::Aim_Up_R;
					else
						state = PlayerState::Aim_Up_L;
				}

				if (INPUT->Press(VK_RIGHT) && INPUT->Press(VK_UP))
				{
					state = PlayerState::Run_R;
					direction = Direction::R;
				}

				if (INPUT->Press(VK_LEFT) && INPUT->Press(VK_UP))
				{
					state = PlayerState::Run_L;
					direction = Direction::L;
				}

				if (INPUT->Press(VK_DOWN))
				{
					if (direction == Direction::R)
						state = PlayerState::Down_R;
					else
						state = PlayerState::Down_L;
				}
			}
		}
	}

	// Dash
	if (dash == 1 && bSpecialAttack == 0 && bSuperBeam == 0)
	{
		jumpSpeed = 0;
		vel = 0;
		state = PlayerState::Dash;
	}
	else if (dash == 2 && deltaTime >= 0.0f && deltaTime < 0.4f && bSpecialAttack == 0 && bSuperBeam == 0)
	{
		jumpSpeed = 0;
		vel = 0;
		state = PlayerState::DashLoop;
	}

	// Super Beam
	if (INPUT->Press('V') && (int)(superMeterCard / maxSuperMeterCard * 100) >= 100 && bSuperBeam == 0)
	{
		superBeam->SetIsSuperBeam(true);
		bSuperBeam = 1;
		check = true;
		if (INPUT->Press(VK_RIGHT) || direction == Direction::R)
		{
			direction = Direction::R;
			state = PlayerState::Super_Beam_R;
			SFXMANAGER->Init(L"SuperIntroR", 1, Vector2(animRect->GetPosition().x - 48 * totalSize, animRect->GetPosition().y + 35 * totalSize), Vector2(318, 217) * 7 * totalSize, 0.0f);
		}
		else if (INPUT->Press(VK_LEFT) || direction == Direction::L)
		{
			direction = Direction::L;
			state = PlayerState::Super_Beam_L;
			SFXMANAGER->Init(L"SuperIntroL", 1, Vector2(animRect->GetPosition().x + 16 * totalSize, animRect->GetPosition().y + 30 * totalSize), Vector2(318, 217) * 7 * totalSize, 0.0f);
		}
	}		// Special Attack
	else if (INPUT->Press('V') && (int)(superMeterCard / maxSuperMeterCard * 100) >= 20 && bSpecialAttack == 0 && !bSuperBeam)
	{
		bSpecialAttack = 1;
		check = true;

		
		if (checkCollider == 0 && jumpCount == 1)
		{
			if (INPUT->Press(VK_RIGHT) || direction == Direction::R)
			{
				direction = Direction::R;
				state = PlayerState::Air_Special_Attack_R;
			}
			else if (INPUT->Press(VK_LEFT) || direction == Direction::L)
			{
				direction = Direction::L;
				state = PlayerState::Air_Special_Attack_L;
			}

			if (INPUT->Press(VK_UP))
			{
				if (direction == Direction::R)
					state = PlayerState::Air_Special_Attack_Up_R;
				else
					state = PlayerState::Air_Special_Attack_Up_L;
			}

			if (INPUT->Press(VK_DOWN))
			{
				if (direction == Direction::R)
					state = PlayerState::Air_Special_Attack_Down_R;
				else
					state = PlayerState::Air_Special_Attack_Down_L;
			}
		}
		else
		{
			animRect->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y + 30 * totalSize));
			if (INPUT->Press(VK_RIGHT) || direction == Direction::R)
			{
				direction = Direction::R;
				state = PlayerState::Special_Attack_R;
			}
			else if (INPUT->Press(VK_LEFT) || direction == Direction::L)
			{
				direction = Direction::L;
				state = PlayerState::Special_Attack_L;
			}

			if (INPUT->Press(VK_UP))
			{
				if (direction == Direction::R)
					state = PlayerState::Special_Attack_Up_R;
				else
					state = PlayerState::Special_Attack_Up_L;
			}
		}
	}

	// Special Attack
	if (bSpecialAttack == 1 && !animRect->GET_COMP(Animator)->GetEnd())
	{
		deltaTime += 1 * DELTA;

		if (deltaTime >= 0.4f && (state == PlayerState::Special_Attack_R || state == PlayerState::Special_Attack_L || state == PlayerState::Air_Special_Attack_R || state == PlayerState::Air_Special_Attack_L))
		{
			if (direction == Direction::R)
				animRect->Move(Vector2(-150, 0));
			else
				animRect->Move(Vector2(150, 0));
		}

		if (hit)
			hit = false;
	}

	if (animRect->GET_COMP(Animator)->GetEnd() && bSpecialAttack == 1)
	{
		superMeterCard = (float)(superMeterCard - 0.2 * maxSuperMeterCard);
		bSpecialAttack = 2;
	}

	if (!INPUT->Press('V') && bSpecialAttack == 2)
	{
		bSpecialAttack = 0;
		deltaTime = 0.0f;
	}

	// Super Beam
	if (bSuperBeam == 1)
	{
		deltaTime += 1 * DELTA;

		if (hit)
			hit = false;
	}

	if (deltaTime >= maxTime && bSuperBeam == 1)
	{
		SOUND->Stop("BeamL");
		superMeterCard = 0;
		bSuperBeam = 2;
		superBeam->SetIsSuperBeam(false);
	}

	if (!INPUT->Press('V') && bSuperBeam == 2)
	{
		bSuperBeam = 0;
		deltaTime = 0.0f;
	}

	// Hit Animation
	if (hp < lastHp && !animRect->GET_COMP(Animator)->GetEnd())
	{
		if (direction == Direction::R)
			state = PlayerState::Hit_R;
		else
			state = PlayerState::Hit_L;
	}
	else if (animRect->GET_COMP(Animator)->GetEnd())
	{
		lastHp = hp;
	}
	else if (hp > lastHp)
		lastHp = hp;

	if (hp == 0)
		state = PlayerState::Death;
		
	if (scale != animRect->GetScale())
		animRect->SetScale(scale * totalSize);

	if (bIntro)
		state = PlayerState::Intro;
	
	switch (state)
	{
	case Idle_R:
		position = animRect->GetPosition();
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"IdleR");
		break;
	case Idle_L:
		position = animRect->GetPosition();
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"IdleL");
		break;
	case Run_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunR");
		animRect->SetScale(Vector2(137, 169)* totalSize);
		break;
	case Run_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunL");
		animRect->SetScale(Vector2(137, 169)* totalSize);
		break;
	case Jump_R:
		if (jumpSpeed >= jumpMaxSpeed * 0.5f)
			SOUND->Play("Jump");
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"JumpR");
		animRect->SetScale(Vector2(88, 109)* totalSize);
		break;
	case Jump_L:
		if (jumpSpeed >= jumpMaxSpeed * 0.5f)
			SOUND->Play("Jump");
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"JumpL");
		animRect->SetScale(Vector2(88, 109)* totalSize);
		break;
	case Parry_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"ParryR");
		animRect->SetScale(Vector2(137, 146) * totalSize);
		if (animRect->GET_COMP(Animator)->GetEnd())
			keyCheck = 0;
		break;
	case Parry_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"ParryL");
		animRect->SetScale(Vector2(137, 146) * totalSize);
		if (animRect->GET_COMP(Animator)->GetEnd())
			keyCheck = 0;
		break;
	case Down_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"DuckR");
		animRect->SetScale(Vector2(168, 92)* totalSize);
		break;
	case Down_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"DuckL");
		animRect->SetScale(Vector2(168, 92)* totalSize);
		break;
	case Shoot_Down_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"ShootDuckR");
		animRect->SetScale(Vector2(178, 81)* totalSize);
		bullet->Init(Vector2(animRect->GetPosition().x + 100 * totalSize, animRect->GetPosition().y), 0.0f, 21.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 80 * totalSize, animRect->GetPosition().y));
		break;
	case Shoot_Down_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"ShootDuckL");
		animRect->SetScale(Vector2(178, 81)* totalSize);
		bullet->Init(Vector2(animRect->GetPosition().x - 100 * totalSize, animRect->GetPosition().y), 180.0f, 21.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 80 * totalSize, animRect->GetPosition().y));
		break;
	case Shoot_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"ShootR");
		animRect->SetScale(Vector2(127, 155)* totalSize);
		bullet->Init(Vector2(animRect->GetPosition().x + 75 * totalSize, animRect->GetPosition().y + 5 * totalSize), 0.0f, 43.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 55 * totalSize, animRect->GetPosition().y + 5 * totalSize));
		break;
	case Shoot_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"ShootL");
		animRect->SetScale(Vector2(127, 155)* totalSize);
		bullet->Init(Vector2(animRect->GetPosition().x - 75 * totalSize, animRect->GetPosition().y + 5 * totalSize), -180.0f, 43.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 55 * totalSize, animRect->GetPosition().y + 5 * totalSize));
		break;
	case Run_Shoot_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunShootR");
		animRect->SetScale(Vector2(144, 162)* totalSize);
		bullet->Init(Vector2(animRect->GetPosition().x + 75 * totalSize, animRect->GetPosition().y - 10 * totalSize), 0.0f, 43.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 55 * totalSize, animRect->GetPosition().y - 10 * totalSize));
		break;
	case Run_Shoot_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunShootL");
		animRect->SetScale(Vector2(144, 162)* totalSize);
		bullet->Init(Vector2(animRect->GetPosition().x - 75 * totalSize, animRect->GetPosition().y - 10 * totalSize), -180.0f, 43.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 55 * totalSize, animRect->GetPosition().y - 10 * totalSize));
		break;
	case Run_Shoot_Diagonal_Up_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunShootDiagUpR");
		animRect->SetScale(Vector2(143, 157)* totalSize);
		bullet->Init(Vector2(animRect->GetPosition().x + 75 * totalSize, animRect->GetPosition().y + 65 * totalSize), -45.0f, 10.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 55 * totalSize, animRect->GetPosition().y + 45 * totalSize));
		break;
	case Run_Shoot_Diagonal_Up_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunShootDiagUpL");
		animRect->SetScale(Vector2(143, 157)* totalSize);
		bullet->Init(Vector2(animRect->GetPosition().x - 75 * totalSize, animRect->GetPosition().y + 65 * totalSize), -135.0f, 10.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 55 * totalSize, animRect->GetPosition().y + 45 * totalSize));
		break;
	case Aim_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimR");
		animRect->SetScale(Vector2(135, 161)* totalSize);
		break;
	case Aim_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimL");
		animRect->SetScale(Vector2(135, 161) * totalSize);
		break;
	case Aim_Diagonal_Up_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimDiagUpR");
		animRect->SetScale(Vector2(129, 151)* totalSize);
		break;
	case Aim_Diagonal_Up_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimDiagUpL");
		animRect->SetScale(Vector2(129, 151)* totalSize);
		break;
	case Aim_Diagonal_Down_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimDiagDownR");
		animRect->SetScale(Vector2(118, 163) * totalSize);
		break;
	case Aim_Diagonal_Down_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimDiagDownL");
		animRect->SetScale(Vector2(118, 163) * totalSize);
		break;
	case Aim_Up_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimUpR");
		animRect->SetScale(Vector2(108, 175) * totalSize);
		break;
	case Aim_Up_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimUpL");
		animRect->SetScale(Vector2(108, 175) * totalSize);
		break;
	case Aim_Down_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimDownR");
		animRect->SetScale(Vector2(103, 168) * totalSize);
		break;
	case Aim_Down_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimDownL");
		animRect->SetScale(Vector2(103, 168) * totalSize);
		break;
	case Aim_Shoot_Diagonal_Up_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimShootDiagUpR");
		animRect->SetScale(Vector2(130, 154) * totalSize);
		bullet->Init(Vector2(animRect->GetPosition().x + 75 * totalSize, animRect->GetPosition().y + 65 * totalSize), -45.0f, 10.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 55 * totalSize, animRect->GetPosition().y + 45 * totalSize));
		break;
	case Aim_Shoot_Diagonal_Up_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimShootDiagUpL");
		animRect->SetScale(Vector2(130, 154) * totalSize);
		bullet->Init(Vector2(animRect->GetPosition().x - 75 * totalSize, animRect->GetPosition().y + 65 * totalSize), -135.0f, 10.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 55 * totalSize, animRect->GetPosition().y + 45 * totalSize));
		break;
	case Aim_Shoot_Diagonal_Down_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimShootDiagDownR");
		animRect->SetScale(Vector2(120, 163) * totalSize);
		bullet->Init(Vector2(animRect->GetPosition().x + 75 * totalSize, animRect->GetPosition().y - 65 * totalSize), 45.0f, 10.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 55 * totalSize, animRect->GetPosition().y - 45 * totalSize));
		break;
	case Aim_Shoot_Diagonal_Down_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimShootDiagDownL");
		animRect->SetScale(Vector2(120, 163) * totalSize);
		bullet->Init(Vector2(animRect->GetPosition().x - 75 * totalSize, animRect->GetPosition().y - 65 * totalSize), 135.0f, 10.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 55 * totalSize, animRect->GetPosition().y - 45 * totalSize));
		break;
	case Aim_Shoot_Up_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimShootUpR");
		animRect->SetScale(Vector2(108, 179) * totalSize);
		bullet->Init(Vector2(animRect->GetPosition().x + 30 * totalSize, animRect->GetPosition().y + 110 * totalSize), -90.0f, 0.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 30 * totalSize, animRect->GetPosition().y + 85 * totalSize));
		break;
	case Aim_Shoot_Up_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimShootUpL");
		animRect->SetScale(Vector2(108, 179) * totalSize);
		bullet->Init(Vector2(animRect->GetPosition().x - 30 * totalSize, animRect->GetPosition().y + 110 * totalSize), -90.0f, 0.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 30 * totalSize, animRect->GetPosition().y + 85 * totalSize));
		break;
	case Aim_Shoot_Down_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimShootDownR");
		animRect->SetScale(Vector2(102, 171) * totalSize);
		bullet->Init(Vector2(animRect->GetPosition().x + 30 * totalSize, animRect->GetPosition().y - 110 * totalSize), 90.0f, 0.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x + 30 * totalSize, animRect->GetPosition().y - 85 * totalSize));
		break;
	case Aim_Shoot_Down_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AimShootDownL");
		animRect->SetScale(Vector2(102, 171) * totalSize);
		bullet->Init(Vector2(animRect->GetPosition().x - 30 * totalSize, animRect->GetPosition().y - 110 * totalSize), 90.0f, 0.0f);
		SFXbullet->SetPosition(Vector2(animRect->GetPosition().x - 30 * totalSize, animRect->GetPosition().y - 85 * totalSize));
		break;
	case Dash:
		SOUND->Play("Dash");
		animRect->SetScale(Vector2(158, 132) * totalSize);
		if (direction == Direction::R)
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"DashR");
		else
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"DashL");
		if (animRect->GET_COMP(Animator)->GetEnd())
			dash = 2;
		break;
	case DashLoop:
		animRect->SetScale(Vector2(347, 165) * totalSize);
		if (direction == Direction::R)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"DashLoopR");
			if ((animRect->GetPosition().x + animRect->GetScale().x * 0.5f) < CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH)
				animRect->Move(Vector2(1000, 0) * totalSize);
		}
		else
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"DashLoopL");
			if ((animRect->GetPosition().x - animRect->GetScale().x * 0.5f) > CAMERA->GetPosition().x)
				animRect->Move(Vector2(-1000, 0) * totalSize);
		}
		break;
	case Special_Attack_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"SpecialAttackR");
		animRect->SetScale(Vector2(425, 385) * totalSize);
		specialAttack->Init(Vector2(animRect->GetPosition().x + 100 * totalSize, animRect->GetPosition().y), 0.0f);
		break;
	case Special_Attack_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"SpecialAttackL");
		animRect->SetScale(Vector2(425, 385) * totalSize);
		specialAttack->Init(Vector2(animRect->GetPosition().x - 100 * totalSize, animRect->GetPosition().y), 180.0f);
		break;
	case Special_Attack_Up_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"SpecialAttackUpR");
		animRect->SetScale(Vector2(353, 396) * totalSize);
		specialAttack->Init(Vector2(animRect->GetPosition().x + 20 * totalSize, animRect->GetPosition().y + 100 * totalSize), -90.0f);
		break;
	case Special_Attack_Up_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"SpecialAttackUpL");
		animRect->SetScale(Vector2(353, 396) * totalSize);
		specialAttack->Init(Vector2(animRect->GetPosition().x - 20 * totalSize, animRect->GetPosition().y + 100 * totalSize), -90.0f);
		break;
	case Air_Special_Attack_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AirSpecialAttackR");
		animRect->SetScale(Vector2(425, 385) * totalSize);
		specialAttack->Init(Vector2(animRect->GetPosition().x + 100 * totalSize, animRect->GetPosition().y), 0.0f);
		break;
	case Air_Special_Attack_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AirSpecialAttackL");
		animRect->SetScale(Vector2(425, 385) * totalSize);
		specialAttack->Init(Vector2(animRect->GetPosition().x - 100 * totalSize, animRect->GetPosition().y), -180.0f);
		break;
	case Air_Special_Attack_Up_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AirSpecialAttackUpR");
		animRect->SetScale(Vector2(353, 396) * totalSize);
		specialAttack->Init(Vector2(animRect->GetPosition().x + 20 * totalSize, animRect->GetPosition().y + 100 * totalSize), -90.0f);
		break;
	case Air_Special_Attack_Up_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AirSpecialAttackUpL");
		animRect->SetScale(Vector2(353, 396) * totalSize);
		specialAttack->Init(Vector2(animRect->GetPosition().x - 20 * totalSize, animRect->GetPosition().y + 100 * totalSize), -90.0f);
		break;
	case Air_Special_Attack_Down_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AirSpecialAttackDownR");
		animRect->SetScale(Vector2(356, 411) * totalSize);
		specialAttack->Init(Vector2(animRect->GetPosition().x + 20 * totalSize, animRect->GetPosition().y - 100 * totalSize), 90.0f);
		break;
	case Air_Special_Attack_Down_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AirSpecialAttackDownL");
		animRect->SetScale(Vector2(356, 411) * totalSize);
		specialAttack->Init(Vector2(animRect->GetPosition().x - 20 * totalSize, animRect->GetPosition().y - 100 * totalSize), 90.0f);
		break;
	case Super_Beam_R:
		superBeam->Init(animRect->GetPosition(), totalSize, deltaTime, maxTime, 0);
		if (deltaTime < 0.9f)
		{
			SOUND->Play("BeamS");
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"SuperBeamIntroR1");
			animRect->SetScale(Vector2(238, 177) * totalSize);
		}
		else if (deltaTime < 1.3f)	// 0.9~1.3
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"SuperBeamIntroR2");
			animRect->SetScale(Vector2(238, 177) * totalSize);
		}
		else
		{
			SOUND->Play("BeamL");
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"SuperBeamLoopR");
			animRect->SetScale(Vector2(202, 140) * totalSize);
		}
		break;
	case Super_Beam_L:
		superBeam->Init(animRect->GetPosition(), totalSize, deltaTime, maxTime, 1);
		if (deltaTime < 0.9f)
		{
			SOUND->Play("BeamS");
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"SuperBeamIntroL1");
			animRect->SetScale(Vector2(238, 177) * totalSize);
		}
		else if (deltaTime < 1.3f)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"SuperBeamIntroL2");
			animRect->SetScale(Vector2(238, 177) * totalSize);
		}
		else
		{
			SOUND->Play("BeamL");
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"SuperBeamLoopL");
			animRect->SetScale(Vector2(202, 140) * totalSize);
		}
		break;
	case Hit_R:
		SOUND->Play("Crack");
		SOUND->Play("Hit");
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"HitR");
		animRect->SetScale(Vector2(125, 188) * totalSize);
		break;
	case Hit_L:
		SOUND->Play("Crack");
		SOUND->Play("Hit");
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"HitL");
		animRect->SetScale(Vector2(125, 188) * totalSize);
		break;
	case Death:
		if (!check)
		{
			check = true;
			SOUND->Play("Crack");
			SOUND->Play("Hit");
			SOUND->Play("Death");
		}
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Death");
		animRect->SetScale(Vector2(172, 106) * totalSize);
		break;
	case Intro:
		deltaTime += DELTA;
		if (deltaTime > 2.0f)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Intro");
			animRect->SetScale(Vector2(152, 169) * totalSize);
			animRect->SetPosition(Vector2(position.x + 7 * totalSize, position.y + 5 * totalSize));
			if (animRect->GET_COMP(Animator)->GetEnd())
			{
				bIntro = false;
				deltaTime = 0.0f;
				animRect->SetPosition(position);
				state = PlayerState::Idle_R;
			}
		}
		break;
	}
	
	// 땅 충돌
	if (!(state >= PlayerState::Special_Attack_R && state <= PlayerState::Super_Beam_L || state == PlayerState::Jump_R || state == PlayerState::Jump_L) && checkCollider)
	{
		animRect->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y + (groundPos.y - (animRect->GetPosition().y - animRect->GetScale().y / 2))));
	}

	bullet->SetTotalSize(totalSize);
	specialAttack->SetTotalSize(totalSize);
	if (INPUT->Press('X') && state != PlayerState::Death && bSpecialAttack != 1 && bSuperBeam != 1)
	{
		bullet->IndexManagement();
	}
	else
		bullet->SetTime((float)(bullet->GetLastIndex() + 1));

	if (bSpecialAttack >= 1 && check && deltaTime >= 0.4f)
	{
		specialAttack->IndexManagement();
		check = false;
	}

	if (superMeterCard > maxSuperMeterCard)
		superMeterCard = maxSuperMeterCard;

	// Sound
	if (state >= PlayerState::Shoot_Down_R && state <= PlayerState::Run_Shoot_Diagonal_Up_L
		|| state >= PlayerState::Aim_Shoot_Diagonal_Up_R && state <= PlayerState::Aim_Shoot_Down_L
		|| state >= PlayerState::Jump_R && state <= PlayerState::Jump_L && INPUT->Press('X'))
	{
		SOUND->Play("Shoot");
	}
	else
		SOUND->Stop("Shoot");


	SFXbullet->Update();
	animRect->Update();
	SFXMANAGER->Update();
	specialAttack->Update();
	superBeam->Update();
	bullet->Update();
}

void Player::Render()
{
	SFXbullet->Render();
	superBeam->Render();
	animRect->Render();
	SFXMANAGER->Render();
	specialAttack->Render();
	bullet->Render();
}

void Player::GUI()
{
	static bool bOpen = true;
	if (ImGui::Begin("Player", &bOpen))
	{
		ImGui::SliderFloat2("Position", (float*)&position, CAMERA->GetPosition().x, CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH);
		ImGui::SliderFloat("Scale", &totalSize, 0.0f, 2.0f, "%.1f");
		ImGui::SliderFloat("Speed", &speed, 100.0f, 2000.0f, "%.1f");

		string textHp = "Player Hp : " + to_string(hp);
		ImGui::Text(textHp.c_str());
		if (ImGui::Button("Down", ImVec2(50, 30)))
			--hp;
		ImGui::SameLine();
		if (ImGui::Button("Up", ImVec2(50, 30)))
			++hp;

		int percent = (int)(superMeterCard / maxSuperMeterCard * 100);
		string textSuperMeterCared = "Player super meter card : " + to_string(percent) + "%%";
		ImGui::Text(textSuperMeterCared.c_str());
		if (ImGui::Button("Down(-10)", ImVec2(70, 30)))
			superMeterCard -= 10;
		ImGui::SameLine();
		if (ImGui::Button("Up(+10)", ImVec2(70, 30)))
			superMeterCard += 10;
	}
	ImGui::End();
}
