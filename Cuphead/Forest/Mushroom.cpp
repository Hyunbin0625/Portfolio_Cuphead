#include "stdafx.h"
#include "Mushroom.h"

Mushroom::Mushroom(const Vector2& position, float totailSize, float poisonSpeed, int maxHp, bool bRegen, float regenTime, Direction direction)
	: state({ ForestEnemyType::Mushroom, position, totailSize, poisonSpeed, maxHp, bRegen, regenTime, direction })
{
	// 초기화
	this->hp = state.maxHp;
	direction = state.direction;
	
	animRect = make_shared<AnimationRect>(position, Vector2(135, 102) * state.totalSize, 0.0f, L"_Textures/Enemy/mushroom_idle_R.png");

	// Move
	// Idle
	animRect->AddAnimClip(make_shared<AnimationClip>(L"IdleR", L"_Textures/Enemy/mushroom_idle_R.png", 8, true, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"IdleL", L"_Textures/Enemy/mushroom_idle_L.png", 8, false, true, 0.1));

	// Attack
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AttackR", L"_Textures/Enemy/mushroom_attack_R.png", 15, true, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AttackL", L"_Textures/Enemy/mushroom_attack_L.png", 15, false, false, 0.1));

	// Pop Out
	animRect->AddAnimClip(make_shared<AnimationClip>(L"PopOutR", L"_Textures/Enemy/mushroom_pop_R.png", 10, true, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"PopOutL", L"_Textures/Enemy/mushroom_pop_L.png", 10, false, false, 0.1));

	// Pop In
	animRect->AddAnimClip(make_shared<AnimationClip>(L"PopInR", L"_Textures/Enemy/mushroom_pop_R.png", 10, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"PopInL", L"_Textures/Enemy/mushroom_pop_L.png", 10, true, false, 0.1));

	// Death
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Death", L"_Textures/Enemy/generic_lg_explosion_a_star_b_40.png", 20, false, false, 0.1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// Components
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));

	// Bullet
	bullet = make_shared<MRPoisonManager>(1, poisonSpeed);

	SOUND->AddSound("MRDeath", L"_Sounds/sfx_platforming_flowergrunt_death_01.wav", false, true);
	SOUND->AddSound("MRShoot", L"_Sounds/sfx_platforming_forest_mushroom_shoot_01.wav");

	SOUND->AddSound("Parry", L"_Sounds/sfx_player_parry_slap_01.wav", false, true);
	SOUND->AddSound("ParryHit", L"_Sounds/sfx_player_parry_power_up_hit_01.wav", false, true);
	SOUND->AddSound("ParryFull", L"_Sounds/sfx_player_parry_power_up_full.wav", false, true);
}

void Mushroom::Collision(shared_ptr<Player> player)
{
	if (animRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && animState != MushroomState::Death)
		player->SetHit(true);

	distance = (float)sqrt(pow(player->GetAnimRect()->GetPosition().x - animRect->GetPosition().x, 2) + pow(player->GetAnimRect()->GetPosition().y - animRect->GetPosition().y, 2));
	
	if (player->GetAnimRect()->GetPosition().x < animRect->GetPosition().x)
		direction = Direction::L;
	else
		direction = Direction::R;

	playerDirection = player->GetDirection();
	
	Vector2 reference = animRect->GetPosition();
	Vector2 point;
	if (direction == Direction::R)
		point = Vector2(player->GetAnimRect()->GetPosition().x + 60 * state.totalSize, player->GetAnimRect()->GetPosition().y + 20 * state.totalSize);
	else
		point = Vector2(player->GetAnimRect()->GetPosition().x - 60 * state.totalSize, player->GetAnimRect()->GetPosition().y + 20 * state.totalSize);

	float R = (float)sqrt(pow((point.x - reference.x), 2) + pow((point.y - reference.y), 2));
	theta = acos((point.x - reference.x) / R);
	theta = (theta * 180) / (float)acos(-1);

	for (int i = 0; i < bullet->GetBullets().size(); ++i)
	{
		if (bullet->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
		{
			if (bullet->GetBullets()[i]->GetParrySlap())
			{
				parryTime += DELTA;
				if (parryTime < 0.5f && player->GetParry())
				{
					SOUND->Play("Parry");
					player->SetJumpSpeed(600.0f);
					player->SetVel(0.0f);
					player->SetSuperMeterCard((float)(player->GetSuperMeterCard() + 0.2 * player->GetMaxSuperMeterCard()));	// 20 퍼센트 추가
					if (player->GetSuperMeterCard() >= 100)
						SOUND->Play("ParryFull");
					else
						SOUND->Play("ParryHit");
					bullet->GetBullets()[i]->SetActivation(false);
					parryTime = 0.0f;
				}
				else if (parryTime >= 0.5f)
				{
					player->SetHit(true);
					parryTime = 0.0f;
				}
			}
			else
			{
				player->SetHit(true);
			}
		}
	}
}

void Mushroom::Init()
{
	bDeathS = false;
	animRect->SetPosition(state.position);
	hp = state.maxHp;
	direction = state.direction;
}

void Mushroom::Destroy()
{
	SOUND->Stop("MRDeath");
	SOUND->Stop("MRShoot");
}

void Mushroom::Update()
{
	if (groundPos.x < -500)
		bGround = false;
	else
		bGround = true;
	
	if (bMod)
	{
		if (!(ImGui::IsAnyItemActive()) && animRect->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			state.position = INPUT->GetMousePosition();
		Init();
		bullet->SetBulletSpeed(state.speed);
	}

	animState = MushroomState::PopIn;

	// 해당 범위에 들어왔을 경우
	if (distance < CENTER_X)
	{
		time += DELTA;

		if (checkState == 0 && (time > 4.0f || (playerDirection && time > 2.0f)))	// || 플레이어와 같은 방향일때
			animState = MushroomState::PopOut;

		if (checkState == 2)
		{
			if (time >= 1.0f && time <= 2.0f)
				animState = MushroomState::Idle;
			else
			{
				animState = MushroomState::PopIn;
				time = 0;
			}
		}
	}
	
	if (checkState == 1)
	{
		animState = MushroomState::Attack;
	}

	if (hp <= 0)
		animState = MushroomState::Death;

	switch (animState)
	{
	case MushroomState::Idle:
		animRect->SetScale(Vector2(102, 114) * state.totalSize);
		if (bGround)
			animRect->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y + (groundPos.y - (animRect->GetPosition().y - animRect->GetScale().y / 2))));
		if (direction == Direction::R)
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"IdleR");
		else
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"IdleL");
		break;
	case MushroomState::Attack:
		animRect->SetScale(Vector2(215, 128) * state.totalSize);
		if (direction == Direction::R)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AttackR");
			bullet->Init(Vector2(state.position.x + 60 * state.totalSize, state.position.y + 20 * state.totalSize), -theta);
		}
		else
		{
			bullet->Init(Vector2(state.position.x - 60 * state.totalSize, state.position.y + 20 * state.totalSize), -theta);
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AttackL");
		}
		if (time > 0.4f && shoot)
		{
			bullet->IndexManagement();
			shoot = false;
		}
		if (animRect->GET_COMP(Animator)->GetEnd())
		{
			checkState = 2;
			time = 1.0f;
		}
		break;
	case MushroomState::PopOut:
		if (!bPopS && animRect->GetPosition().y != -1000 && animRect->GetPosition().x <= CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH && animRect->GetPosition().x >= CAMERA->GetPosition().x)
		{
			bPopS = true;
			SOUND->Play("MRShoot");
		}
		animRect->SetScale(Vector2(121, 135) * state.totalSize);
		if (direction == Direction::R)
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"PopOutR");
		else
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"PopOutL");
		if (animRect->GET_COMP(Animator)->GetEnd())
		{
			bPopS = false;
			checkState = 1;
			time = 0.0f;
			shoot = true;
		}
		break;
	case MushroomState::PopIn:
		animRect->SetScale(Vector2(121, 135) * state.totalSize);
		if (direction == Direction::R)
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"PopInR");
		else
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"PopInL");
		if (animRect->GET_COMP(Animator)->GetEnd())
			checkState = 0;
		break;
	case MushroomState::Death:
		if (!bDeathS && animRect->GetPosition().y != -1000 && animRect->GetPosition().x <= CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH && animRect->GetPosition().x >= CAMERA->GetPosition().x)
		{
			bDeathS = true;
			SOUND->Play("MRDeath");
		}
		animRect->SetScale(Vector2(234, 261) * (float)(0.6 * state.totalSize));
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Death");
		if (animRect->GET_COMP(Animator)->GetEnd())
			animRect->SetPosition(Vector2(1000, -1000));
		break;
	}
	bullet->SetTotalSize(state.totalSize);
	animRect->Update();
	bullet->Update();
}

void Mushroom::Render()
{
	animRect->Render();
	bullet->Render();
}

void Mushroom::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ". Mushroom";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		animRect->SetOutline(true);

		ImGui::Text(objName.c_str());

		ImGui::SliderFloat2("Position", (float*)&state.position, CAMERA->GetPosition().x, CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH);
		ImGui::SliderFloat("Size", &state.totalSize, 0.1f, 5.0f, "%.2f");
		ImGui::SliderFloat("PoisonSpeed", &state.speed, 100.0f, 700.0f, "%.2f");
		ImGui::InputInt("MaxHp", &state.maxHp);
		
		ImGui::Checkbox("Regen", &state.bRegen);
		ImGui::SliderFloat("RegenTime", &state.regenTime, 0.0f, 60.0f, "%.2f");
		

		bool r = 0, l = 0;
		if (state.direction)
			l = 1;
		else
			r = 1;
		ImGui::Text("Default direction");
		if (ImGui::Checkbox("L", &l))
		{
			state.direction = Direction::L;
			r = 0;
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("R", &r))
		{
			state.direction = Direction::R;
			l = 0;
		}
	
		if (ImGui::Button("Delete", ImVec2(50, 30)))
			bDelete = 1;

		ImGui::EndMenu();
	}
	else
	{
		animRect->SetOutline(false);
	}
}