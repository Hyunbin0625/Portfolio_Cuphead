#include "stdafx.h"
#include "AcornMachine.h"

AcornMachine::AcornMachine(const Vector2& position, float totailSize, float speed, int maxHp, bool bRegen, float regenTime, Direction direction)
	: state({ ForestEnemyType::AcornMachine, position, totailSize, speed, maxHp, bRegen, regenTime, direction })
{
	// 초기화
	this->hp = state.maxHp;
	direction = state.direction;
	
	animRect = make_shared<AnimationRect>(Vector2(position), Vector2(530, 534) * state.totalSize, 0.0f, L"_Textures/Enemy/acorn_machine_idle.png");

	// Move
	// 	Idle
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Idle", L"_Textures/Enemy/acorn_machine_idle.png", 20, false, true, 0.09));

	// Death
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Death", L"_Textures/Enemy/acorn_machine_death.png", 18, false, false, 0.1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// Components
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));


	// backer
	animRect1 = make_shared<AnimationRect>(position, Vector2(530, 534) * state.totalSize, 0.0f, L"_Textures/Enemy/acorn_machine_idle_backer.png");

	// Idle
	animRect1->AddAnimClip(make_shared<AnimationClip>(L"BIdle", L"_Textures/Enemy/acorn_machine_idle_backer.png", 20, false, true, 0.09));

	// AddAnimator
	animRect1->AddComponent(make_shared<AnimatorComponent>(animRect1->GetAnimClips()));
	// animRect SetAnimator
	animRect1->SetAnimator(animRect1->GET_COMP(Animator));


	// FlowerGrunt
	animRect2 = make_shared<AnimationRect>(Vector2(position.x + 245 * state.totalSize, position.y - 150 * state.totalSize), Vector2(243, 237) * state.totalSize, 0.0f, L"_Textures/Enemy/acorn_machine_flower_grunt.png");

	// Idle
	animRect2->AddAnimClip(make_shared<AnimationClip>(L"FGIdle", L"_Textures/Enemy/acorn_machine_flower_grunt.png", 12, false, true, 0.09));

	// AddAnimator
	animRect2->AddComponent(make_shared<AnimatorComponent>(animRect2->GetAnimClips()));
	// animRect SetAnimator
	animRect2->SetAnimator(animRect2->GET_COMP(Animator));

	// acorn
	acorn = make_shared<Acorn>(position, totailSize, speed, 3, true, regenTime, Direction::L);

	SOUND->AddSound("AMGrunt", L"_Sounds/sfx_platforming_acorn_maker_grunt_01-02.wav", true);
	SOUND->AddSound("AMDeath", L"_Sounds/sfx_platforming_acorn_maker_death_01.wav", false, true);
}

void AcornMachine::Collision(shared_ptr<Player> player)
{
	acorn->Collision(player);

	if (animRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && animState != AcornMachineState::Death)
		player->SetHit(true);

	// 범위 활성화
	if (player->GetAnimRect()->GetPosition().x >= state.position.x - WIN_DEFAULT_WIDTH)
	{
		if (acorn->GetHp() <= 0 && acorn->GetTime() >= state.regenTime)
			animState = AcornMachineState::Create;
	}
	else
		animState = AcornMachineState::Idle;

	if (animState != AcornMachineState::Create)
	{
		for (int i = 0; i < player->GetBullet()->GetBullets().size(); ++i)
		{
			if (player->GetBullet()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(acorn->GetAnimRect()->GET_COMP(Collider)) && acorn->GetHp() > 0)
			{
				if (!player->GetBullet()->GetBullets()[i]->GetHit())
				{
					player->GetBullet()->GetBullets()[i]->SetIsHit(true);
					player->SetSuperMeterCard(player->GetSuperMeterCard() + 1);
					acorn->SetHit(true);
				}
			}
		}

		for (int i = 0; i < player->GetSpecialAttack()->GetBullets().size(); ++i)
		{
			if (player->GetSpecialAttack()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(acorn->GetAnimRect()->GET_COMP(Collider)) && acorn->GetHp() > 0)
				acorn->SetHit(true);
		}

		if (player->GetSuperBeam()->GetAnimRect()->GET_COMP(Collider)->Intersect(acorn->GetAnimRect()->GET_COMP(Collider)) && acorn->GetHp() > 0)
			acorn->SetHit(true);
	}
}

void AcornMachine::Init()
{
	bDeathS = false;
	animRect->SetPosition(state.position);
	animRect1->SetPosition(state.position);
	animRect2->SetPosition(Vector2(state.position.x + 245 * state.totalSize, state.position.y - 150 * state.totalSize));
	acorn->SetState({ acorn->GetState().type, Vector2(state.position.x + 30 * state.totalSize, state.position.y), state.totalSize,
		state.speed, acorn->GetState().maxHp, acorn->GetState().bRegen, state.regenTime, acorn->GetState().direction });
	acorn->SetAcornState(AcornState::DropLoop);
	direction = state.direction;
	hp = state.maxHp;
}

void AcornMachine::Destroy()
{
	SOUND->Stop("AMGrunt");
	SOUND->Stop("AMDeath");
}

void AcornMachine::Update()
{
	if (bMod)
	{
		if (!(ImGui::IsAnyItemActive()) && animRect->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			state.position = INPUT->GetMousePosition();
		Init();
	}

	if (hp <= 0)
	{
		animState = AcornMachineState::Death;
		animRect1->SetPosition(Vector2(1000, -1000));
		animRect2->SetPosition(Vector2(1000, -1000));
		acorn->SetHp(0);
	}
	switch (animState)
	{
	case AcornMachineState::Death:
		if (!bDeathS && animRect->GetPosition().x <= CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH && animRect->GetPosition().x >= CAMERA->GetPosition().x)
		{
			bDeathS = true;
			bFGruntS = false;
			SOUND->Stop("AMGrunt");
			SOUND->Play("AMDeath");
		}
		animRect->SetScale(Vector2(894, 675) * state.totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Death");
		if (animRect->GET_COMP(Animator)->GetEnd())
		{
			bFGruntS = false;
			animRect->SetPosition(Vector2(1000, -1000));
		}
		break;
	case AcornMachineState::Create:
		if (!check)
		{
			check = true;
			acorn->Init();
			acorn->SetMachine(true);
		}
		acorn->GetAnimRect()->Move(Vector2(0, 200));
		if (acorn->GetAnimRect()->GetPosition().y >= CAMERA->GetPosition().y + WIN_DEFAULT_HEIGHT - 100)
		{
			acorn->SetMachine(false);
			animState = AcornMachineState::Idle;
			check = false;
		}
	case AcornMachineState::Idle:
		if (animRect->GetPosition().x <= CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH && animRect->GetPosition().x >= CAMERA->GetPosition().x)
		{
			if (!bFGruntS)
			{
				bFGruntS = true;
				SOUND->Play("AMGrunt");
			}
		}
		else
		{
			if (bFGruntS)
			{
				bFGruntS = false;
				SOUND->Stop("AMGrunt");
			}
		}
		animRect->SetScale(Vector2(530, 534) * state.totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Idle");
		animRect1->SetScale(Vector2(530, 534) * state.totalSize);
		animRect1->GET_COMP(Animator)->SetCurrentAnimClip(L"BIdle");
		animRect2->SetScale(Vector2(243, 237) * state.totalSize);
		animRect2->GET_COMP(Animator)->SetCurrentAnimClip(L"FGIdle");
	}

	animRect1->Update();
	acorn->Update();
	animRect2->Update();
	animRect->Update();
}

void AcornMachine::Render()
{
	animRect1->Render();
	acorn->Render();
	animRect2->Render();
	animRect->Render();
}

void AcornMachine::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ". AcornMachine";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		animRect->SetOutline(true);

		ImGui::Text(objName.c_str());

		ImGui::SliderFloat2("Position", (float*)&state.position, CAMERA->GetPosition().x, CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH);
		ImGui::SliderFloat("Size", &state.totalSize, 0.1f, 5.0f, "%.2f");
		ImGui::SliderFloat("AcornSpeed", &state.speed, 200.0f, 1000.0f, "%.2f");
		ImGui::InputInt("MaxHp", &state.maxHp);

		ImGui::SliderFloat("AcornRegenTime", &state.regenTime, 0.0f, 60.0f, "%.2f");
		

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
