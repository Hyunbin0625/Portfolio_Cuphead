#include "stdafx.h"
#include "Player.h"

Player::Player(const Vector2& position, const Vector2& scale, float speed)
	: position(position), scale(scale), speed(speed)
{
	animRect = make_unique<AnimationRect>(position, scale, 0.0f, L"_Textures/Player/cuphead_idle_R.png");

	// Move
	// Idle
	animRect->AddAnimClip(make_shared<AnimationClip>(L"IdleR", L"_Textures/Player/cuphead_idle_R.png", 8, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"IdleL", L"_Textures/Player/cuphead_idle_L.png", 8, true, true, 0.1));
	// Run
	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunR", L"_Textures/Player/cuphead_run_R.png", 16, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunL", L"_Textures/Player/cuphead_run_L.png", 16, true, true, 0.1));

	// TrunRun
//	animRect->AddAnimClip(make_shared<AnimationClip>(L"TrunRunR", L"_Textures/Player/cuphead_trunrun_R.png", 2, false, true, 0.1));
//	animRect->AddAnimClip(make_shared<AnimationClip>(L"TrunRunL", L"_Textures/Player/cuphead_trunrun_L.png", 2, true, true, 0.1));

	// Jump
	animRect->AddAnimClip(make_shared<AnimationClip>(L"JumpR", L"_Textures/Player/cuphead_jump_R.png", 6, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"JumpL", L"_Textures/Player/cuphead_jump_L.png", 6, true, true, 0.1));

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
	animRect->AddAnimClip(make_shared<AnimationClip>(L"DuckR", L"_Textures/Player/cuphead_duck_R.png", 11, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"DuckL", L"_Textures/Player/cuphead_duck_L.png", 11, true, true, 0.1));

	// Shoot_Duck
//	animRect->AddAnimClip(make_shared<AnimationClip>(L"ShootDuckR", L"_Textures/Player/cuphead_duck_R.png", 11, false, true, 0.1));
//	animRect->AddAnimClip(make_shared<AnimationClip>(L"ShootDuckL", L"_Textures/Player/cuphead_duck_L.png", 11, true, true, 0.1));

	// Aim
	
	// Aim_Diagonal_Up

	// Aim_Diagonal_Down

	// Aim_Up

	// Aim_Down


	// Aim_Shoot_Diagonal_Up

	// Aim_Shoot_Diagonal_Down

	// Aim_Shoot_Up

	// Aim_Shoot_Down


	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	bullet = make_shared<PlayerBullet>(20, 800, 5, L"_Textures/Player/weapon_peashot_main.png");	// totalBullet, bulletSpeed, speakerSpeed, texturePath

	// Components
	animRect->AddComponent(make_shared<MoveComponent>(speed));
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void Player::Move()
{

}

void Player::Jump()
{

}

bool Player::CheckGround(shared_ptr<ColorRect> ground)
{
	checkCollider = 0;
	if (animRect->GET_COMP(Collider)->Intersect(ground->GET_COMP(Collider)))
	{
		checkCollider = 1;
		return true;
	}

	return false;
}

void Player::Init()
{
}

void Player::Destroy()
{
	animRect.reset();
}

void Player::Update()
{
	if (checkCollider == 0)
	{
		G += 15 * DELTA;
		jumpSpeed -= G;

		if (direction == Direction::R)
		{
			state = State::Jump_R;
		}

		if (direction == Direction::L)
		{
			state = State::Jump_L;
		}
	}
	else
	{
		jumpCount = 0;
		G = 0;
		speedG = 0;

		if (INPUT->Press(VK_RIGHT))
		{
			state = State::Run_R;
			direction = Direction::R;
		}
		else if (direction == Direction::R)
		{
			state = State::Idle_R;
		}

		if (INPUT->Press(VK_LEFT))
		{
			state = State::Run_L;
			direction = Direction::L;
		}
		else if (direction == Direction::L)
		{
			state = State::Idle_L;
		}

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
					cout << "Aim_Shoot_Down\n";
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
					cout << "Shoot_Down\n";
				}
			}
			else	// 이동
			{
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
						state = State::Down_R;
					else
						state = State::Down_L;
				}
			}
		}
	}

	animRect->SetScale(Vector2(101, 159));
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
		break;
	case Run_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunL");
		break;
	case Jump_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"JumpR");
		break;
	case Jump_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"JumpL");
		break;
	case Down_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"DuckR");
		lastPos.y = animRect->GetPosition().y;
		animRect->SetScale(Vector2(168, 92));	// Duck_size	나중에 매크로로 저장
		break;
	case Down_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"DuckL");
		lastPos.y = animRect->GetPosition().y;
		animRect->SetScale(Vector2(168, 92));
		break;
	case Shoot_Down_R:
//		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"ShootDuckR");
		bullet->SetPosition(Vector2(animRect->GetPosition().x + 70, animRect->GetPosition().y - 40));
		bullet->SetRotation(0.0f);
		break;
	case Shoot_Down_L:
//		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"ShootDuckL");
		bullet->SetPosition(Vector2(animRect->GetPosition().x - 70, animRect->GetPosition().y - 40));
		bullet->SetRotation(180.0f);
		break;
	case Shoot_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"ShootR");
		bullet->SetPosition(Vector2(animRect->GetPosition().x + 70, animRect->GetPosition().y + 20));
		bullet->SetRotation(0.0f);
		break;
	case Shoot_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"ShootL");
		bullet->SetPosition(Vector2(animRect->GetPosition().x - 100, animRect->GetPosition().y + 20));
		bullet->SetRotation(-180.0f);
		break;
	case Run_Shoot_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunShootR");
		bullet->SetPosition(Vector2(animRect->GetPosition().x + 100, animRect->GetPosition().y + 0));
		bullet->SetRotation(0.0f);
		break;
	case Run_Shoot_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunShootL");
		bullet->SetPosition(Vector2(animRect->GetPosition().x - 100, animRect->GetPosition().y + 10));
		bullet->SetRotation(-180.0f);
		break;
	case Run_Shoot_Diagonal_Up_R:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunShootDiagUpR");
		bullet->SetPosition(Vector2(animRect->GetPosition().x + 100, animRect->GetPosition().y + 90));
		bullet->SetRotation(-45.0f);
		break;
	case Run_Shoot_Diagonal_Up_L:
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunShootDiagUpL");
		bullet->SetPosition(Vector2(animRect->GetPosition().x - 100, animRect->GetPosition().y + 90));
		bullet->SetRotation(-135.0f);
		break;
	case Aim_R:
		break;
	case Aim_L:
		break;
	case Aim_Diagonal_Up_R:
		break;
	case Aim_Diagonal_Up_L:
		break;
	case Aim_Diagonal_Down_R:
		break;
	case Aim_Diagonal_Down_L:
		break;
	case Aim_Up_R:
		break;
	case Aim_Up_L:
		break;
	case Aim_Down_R:
		break;
	case Aim_Down_L:
		break;
	case Aim_Shoot_Diagonal_Up_R:
		bullet->SetPosition(Vector2(animRect->GetPosition().x + 70, animRect->GetPosition().y + 40));
		bullet->SetRotation(-45.0f);
		break;
	case Aim_Shoot_Diagonal_Up_L:
		bullet->SetPosition(Vector2(animRect->GetPosition().x - 70, animRect->GetPosition().y + 40));
		bullet->SetRotation(-135.0f);
		break;
	case Aim_Shoot_Diagonal_Down_R:
		bullet->SetPosition(Vector2(animRect->GetPosition().x + 70, animRect->GetPosition().y - 40));
		bullet->SetRotation(45.0f);
		break;
	case Aim_Shoot_Diagonal_Down_L:
		bullet->SetPosition(Vector2(animRect->GetPosition().x - 70, animRect->GetPosition().y - 40));
		bullet->SetRotation(135.0f);
		break;
	case Aim_Shoot_Up_R:
		bullet->SetPosition(Vector2(animRect->GetPosition().x + 20, animRect->GetPosition().y + 90));
		bullet->SetRotation(-90.0f);
		break;
	case Aim_Shoot_Up_L:
		bullet->SetPosition(Vector2(animRect->GetPosition().x - 20, animRect->GetPosition().y + 90));
		bullet->SetRotation(-90.0f);
		break;
	case Aim_Shoot_Down_R:
		bullet->SetPosition(Vector2(animRect->GetPosition().x + 20, animRect->GetPosition().y - 90));
		bullet->SetRotation(90.0f);
		break;
	case Aim_Shoot_Down_L:
		bullet->SetPosition(Vector2(animRect->GetPosition().x - 20, animRect->GetPosition().y - 90));
		bullet->SetRotation(90.0f);
		break;
	}

	if (INPUT->Down('Z') && checkCollider == 1)
	{
		++jumpCount;
		G = 0;
		speedG = 0;
		jumpSpeed = jumpMaxSpeed;

		checkCollider = 0;
	}

	// JumpMove
	if (checkCollider == 0)
	{
		animRect->Move(Vector2(0, jumpSpeed));
	}

	animRect->Update();
	bullet->Update();
}

void Player::PreRender()
{
}

void Player::Render()
{
	animRect->Render();
	bullet->Render();
}

void Player::PostRender()
{
}
