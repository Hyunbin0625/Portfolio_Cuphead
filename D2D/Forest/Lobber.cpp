#include "stdafx.h"
#include "Lobber.h"

Lobber::Lobber(const Vector2& position, float totailSize, float seedSpeed, int maxHp, bool bRegen, float regenTime, Direction direction)
	: state({ ForestEnemyType::Lobber, position, totailSize, seedSpeed, maxHp, bRegen, regenTime, direction })
{
	// 초기화
	this->hp = state.maxHp;
	direction = state.direction;
	
	animRect = make_shared<AnimationRect>(position, Vector2(141, 213) * state.totalSize, 0.0f, L"_Textures/Enemy/lobber_idle_L.png");

	// Move
	// Idle
	animRect->AddAnimClip(make_shared<AnimationClip>(L"IdleR", L"_Textures/Enemy/lobber_idle_R.png", 15, false, false, 0.09));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"IdleL", L"_Textures/Enemy/lobber_idle_L.png", 15, false, false, 0.09));

	// Attack
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Attack", L"_Textures/Enemy/lobber_attack.png", 15, false, false, 0.1));

	// Death
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Death", L"_Textures/Enemy/generic_lg_explosion_a_star_b_40.png", 20, false, false, 0.1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// Components
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));

	// Bullet
	bullet = make_shared<LSeedManager>(1, seedSpeed);
}

void Lobber::Collision(shared_ptr<Player> player)
{
	if (animRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && animState != LobberState::Death)
		player->SetHit(true);

	distance = sqrt(pow(player->GetAnimRect()->GetPosition().x - animRect->GetPosition().x, 2) + pow(player->GetAnimRect()->GetPosition().y - animRect->GetPosition().y, 2));
	playerX = player->GetAnimRect()->GetPosition().x;
	
	for (int i = 0; i < bullet->GetBullets().size(); ++i)
	{
		if (bullet->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
		{
			player->SetHit(true);
		}
	}
}

void Lobber::Init()
{
	animRect->SetPosition(state.position);
	hp = state.maxHp;
	direction = state.direction;
}

void Lobber::Update()
{
	if (groundPos.x < -500)
		bGround = false;
	else
		bGround = true;
	
	if (bMod)
	{
		if (!(ImGui::IsAnyItemActive()) && animRect->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			state.position = INPUT->GetMousePosition();
		animRect->SetPosition(state.position);
		direction = state.direction;
		hp = state.maxHp;

		bullet->SetBulletSpeed(state.speed);
	}

	animState = LobberState::Idle;

	// 해당 범위에 들어왔을 경우
	if (checkAttack)
		animState = LobberState::Attack;

	if (hp <= 0)
		animState = LobberState::Death;

	switch (animState)
	{
	case LobberState::Idle:
		animRect->SetScale(Vector2(141, 213) * state.totalSize);
		animRect->SetPosition(state.position);
		if (bGround)
			animRect->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y + (groundPos.y - (animRect->GetPosition().y - animRect->GetScale().y / 2))));
		if (direction == Direction::R)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"IdleR");
			if (animRect->GET_COMP(Animator)->GetEnd())
			{
				direction = Direction::L;
				++count;
				if (distance < CENTER_X && count >= 2)
				{
					checkAttack = true;
					shoot = true;
					count = 0;
				}
			}
		}
		else
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"IdleL");
			if (animRect->GET_COMP(Animator)->GetEnd())
			{
				direction = Direction::R;
				++count;
				if (distance < CENTER_X && count >= 2)
				{
					checkAttack = true;
					shoot = true;
					count = 0;
				}
			}
		}
		break;
	case LobberState::Attack:
		time += DELTA;
		animRect->SetScale(Vector2(131, 247) * state.totalSize);
		animRect->SetPosition(Vector2(state.position.x + 11 * state.totalSize, state.position.y));
		if (bGround)
			animRect->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y + (groundPos.y - (animRect->GetPosition().y - animRect->GetScale().y / 2))));
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Attack");
		bullet->Init(Vector2(state.position.x, state.position.y + 100 * state.totalSize), 0.0f, playerX);
		if (time > 0.4f && shoot)
		{
			bullet->IndexManagement();
			shoot = false;
		}
		if (animRect->GET_COMP(Animator)->GetEnd())
		{
			checkAttack = false;
			time = 0;
		}
		break;
	case LobberState::Death:
		animRect->SetScale(Vector2(234, 261) * state.totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Death");
		if (animRect->GET_COMP(Animator)->GetEnd())
			animRect->SetPosition(Vector2(1000, -1000));
		break;
	}

	bullet->SetTotalSize(state.totalSize);
	animRect->Update();
	bullet->Update();
}

void Lobber::Render()
{
	animRect->Render();
	bullet->Render();
}

void Lobber::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ". Lobber";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		animRect->SetOutline(true);

		ImGui::Text(objName.c_str());

		ImGui::SliderFloat2("Position", (float*)&state.position, CAMERA->GetPosition().x, CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH);
		ImGui::SliderFloat("Size", &state.totalSize, 0.1f, 5.0f, "%.2f");
		ImGui::SliderFloat("SeedSpeed", &state.speed, 0.0f, 100.0f, "%.2f");
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