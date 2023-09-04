#include "stdafx.h"
#include "Spiker.h"

Spiker::Spiker(const Vector2& position, float totailSize, float speed, int maxHp, bool bRegen, float range, Direction direction)
	: state({ ForestEnemyType::Spiker, position, totailSize, speed, maxHp, bRegen, range, direction })
{
	// 초기화
	bActivation = true;
	parryTime = 0.0f;

	animRect = make_shared<AnimationRect>(position, Vector2(91, 92) * state.totalSize, 0.0f, L"_Textures/Enemy/pink_spiker.png");

	// Move
	// Attack
	animRect->AddAnimClip(make_shared<AnimationClip>(L"PinkSpiker", L"_Textures/Enemy/pink_spiker.png", 6, false, true, 0.1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// Components
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));

	SOUND->AddSound("Parry", L"_Sounds/sfx_player_parry_slap_01.wav", false, true);
	SOUND->AddSound("ParryHit", L"_Sounds/sfx_player_parry_power_up_hit_01.wav", false, true);
	SOUND->AddSound("ParryFull", L"_Sounds/sfx_player_parry_power_up_full.wav", false, true);
}

void Spiker::Collision(shared_ptr<Player> player)
{
	if (animRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
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
			bActivation = false;
			parryTime = 0.0f;
		}
		else if (parryTime >= 0.5f)
		{
			player->SetHit(true);
			parryTime = 0.0f;
		}
	}
}

void Spiker::Init()
{
	animRect->SetPosition(state.position);
	bActivation = true;
}

void Spiker::Destroy()
{
	SOUND->Stop("Parry");
	SOUND->Stop("ParryHit");
	SOUND->Stop("ParryFull");
}

void Spiker::Update()
{
	if (!bActivation)
		animRect->SetPosition(Vector2(1000, -1000));

	if (bMod)
	{
		if (!(ImGui::IsAnyItemActive()) && animRect->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			state.position = INPUT->GetMousePosition();
		Init();
	}

	float temp = 0.0f;
	if (state.direction == Direction::R)
		temp = (state.position.y + state.regenTime) - animRect->GetPosition().y;
	else
		temp = (state.position.y - state.regenTime) - animRect->GetPosition().y;

	if (state.direction == Direction::R && temp <= 50.0f)
		state.direction = Direction::L;
	else if (state.direction == Direction::L && temp >= -50.0f)
		state.direction = Direction::R;

	animRect->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y + temp * state.speed * DELTA));

	if (bActivation)
		animRect->Update();
}

void Spiker::Render()
{
	if (bActivation)
		animRect->Render();
}

void Spiker::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ". Spiker";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		animRect->SetOutline(true);

		ImGui::Text(objName.c_str());

		ImGui::SliderFloat2("Position", (float*)&state.position, CAMERA->GetPosition().x, CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH);
		ImGui::SliderFloat("Size", &state.totalSize, 0.1f, 5.0f, "%.2f");
		ImGui::SliderFloat("Speed", &state.speed, 0.0f, 5.0f, "%.2f");
		ImGui::SliderFloat("Range", &state.regenTime, 0.0f, 1000.0f, "%.2f");
	
		if (ImGui::Button("Delete", ImVec2(50, 30)))
			bDelete = 1;

		ImGui::EndMenu();
	}
	else
	{
		animRect->SetOutline(false);
	}
}