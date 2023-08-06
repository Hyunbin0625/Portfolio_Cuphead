#include "stdafx.h"
#include "Chomper.h"

Chomper::Chomper(const Vector2& position, float totailSize, float speed, int maxHp, bool bRegen, float regenTime, Direction direction)
	: state({ ForestEnemyType::Chomper, position, totailSize, speed, maxHp, bRegen, regenTime, direction })
{
	// 초기화
	time = (float)maxHp;	// maxHp를 재활용해, time 추가
	G = 0.0f;
	jumpSpeed = speed;

	animRect = make_shared<AnimationRect>(position, Vector2(196, 486) * state.totalSize, 0.0f, L"_Textures/Enemy/chomper_attack.png");

	// Move
	// Attack
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Attack", L"_Textures/Enemy/chomper_attack.png", 16, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AttackLoop", L"_Textures/Enemy/chomper_attack_loop.png", 4, false, true, 0.1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// Components
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void Chomper::Collision(shared_ptr<Player> player)
{
	if (animRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
		player->SetHit(true);
}

void Chomper::Init()
{
	animRect->SetPosition(state.position);
	G = 0.0f;
	time = 0.0f;
	jumpSpeed = state.speed;
}

void Chomper::Update()
{
	if (bMod)
	{
		if (!(ImGui::IsAnyItemActive()) && animRect->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			state.position = INPUT->GetMousePosition();
		animRect->SetPosition(state.position);
	}

	time += DELTA;

	if (time >= state.regenTime)
	{
		G += (float)(9.8 * DELTA);
		jumpSpeed -= G;

		if (bAttackLoop)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AttackLoop");
			if (animRect->GetPosition().y <= state.position.y)
			{
				bAttackLoop = false;
				Init();
			}
		}
		else 
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Attack");
			if (animRect->GET_COMP(Animator)->GetEnd())
				bAttackLoop = true;
		}

		animRect->Move(Vector2(0, jumpSpeed));
	}

	animRect->Update();
}

void Chomper::Render()
{
	animRect->Render();
}

void Chomper::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ". Chomper";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		animRect->SetOutline(true);

		ImGui::Text(objName.c_str());

		ImGui::SliderFloat2("Position", (float*)&state.position, CAMERA->GetPosition().x, CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH);
		ImGui::SliderFloat("Size", &state.totalSize, 0.1f, 5.0f, "%.2f");
		ImGui::SliderFloat("JumpSpeed", &state.speed, 700.0f, 3000.0f, "%.2f");
		
		ImGui::InputInt("AddTime(int)", &state.maxHp);
		ImGui::SliderFloat("RegenTime", &state.regenTime, 1.0f, 50.0f, "%.2f");
	
		if (ImGui::Button("Delete", ImVec2(50, 30)))
			bDelete = 1;

		ImGui::EndMenu();
	}
	else
	{
		animRect->SetOutline(false);
	}
}