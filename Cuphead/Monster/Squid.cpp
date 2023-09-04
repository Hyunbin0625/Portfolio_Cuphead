#include "stdafx.h"
#include "Squid.h"

Squid::Squid()
{
	animRect = make_shared<AnimationRect>(Vector2(1000, -1000), Vector2(), 0.0f, L"_Textures/Pirate/pirate_squid_entrance.png");
	dust = make_shared<AnimationRect>(Vector2(1000, -1000), Vector2(758, 302), 0.0f, L"_Textures/Pirate/pirate_squid_splash.png");

	// Intro
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Intro", L"_Textures/Pirate/pirate_squid_entrance.png", 18, false, false, 0.12f));

	// Attack
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AttackS", L"_Textures/Pirate/pirate_squid_start.png", 3, false, false, 0.12f));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AttackL", L"_Textures/Pirate/pirate_squid_loop.png", 15, false, true, 0.12f));

	// Leave
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Leave", L"_Textures/Pirate/pirate_squid_leave.png", 22, false, false, 0.12f));

	// Dust
	dust->AddAnimClip(make_shared<AnimationClip>(L"Dust", L"_Textures/Pirate/pirate_squid_splash.png", 13, false, false, 0.1f));

	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	dust->AddComponent(make_shared<AnimatorComponent>(dust->GetAnimClips()));

	animRect->SetAnimator(animRect->GET_COMP(Animator));
	dust->SetAnimator(dust->GET_COMP(Animator));

	// Sound
	SOUND->AddSound("SquidEneter", L"_Sounds/sfx_pirate_squid_enter.wav");
	SOUND->AddSound("SquidAttack", L"_Sounds/sfx_pirate_squid_attack_loop.wav", true);
	SOUND->AddSound("SquidExit", L"_Sounds/sfx_pirate_squid_exit.wav");
}

Squid::~Squid() {}

void Squid::Collision(shared_ptr<Player> player)
{
}

void Squid::Init(Vector2 position, float size)
{
	state = SquidState::Intro;
	this->position = position;
	this->totalSize = size;
	animRect->GET_COMP(Animator)->ResetFrame();
	dust->GET_COMP(Animator)->ResetFrame();
}

void Squid::Update()
{
	switch (state)
	{
	case SquidState::None:
		animRect->SetPosition(Vector2(1000, -1000));
		dust->SetPosition(Vector2(1000, -1000));
		break;
	case SquidState::Intro:
		SOUND->Play("SquidEneter");
		animRect->SetPosition(position);
		animRect->SetScale(Vector2(489, 544));
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Intro");

		dust->SetPosition(animRect->GetPosition() + Vector2(-40, -100) * totalSize);
		dust->SetScale(Vector2(758, 302));
		dust->GET_COMP(Animator)->SetCurrentAnimClip(L"Dust");

		if (dust->GET_COMP(Animator)->GetEnd())
			dust->SetPosition(Vector2(1000, -1000));

		if (animRect->GET_COMP(Animator)->GetEnd())
			state = SquidState::Loop;
		break;
	case SquidState::Loop:
		if (animCount == 0)
		{
			animRect->SetPosition(position);
			animRect->SetScale(Vector2(587, 537));
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AttackS");
			if (animRect->GET_COMP(Animator)->GetEnd())
				++animCount;
		}
		else
		{
			SOUND->Play("SquidAttack");
			animRect->SetPosition(position);
			animRect->SetScale(Vector2(587, 537));
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"AttackL");
			SQUIDBULLETMANAGER->Init(animRect->GetPosition(), totalSize, animRect->GET_COMP(Animator)->GetCurrentFrameIndex());

			time += DELTA;
			if (time >= attackTime)
			{
				SOUND->Stop("SquidAttack");
				animCount = 0;
				time = 0.0f;
				SQUIDBULLETMANAGER->SetActivation(false);
				state = SquidState::Leave;
			}
		}
		break;
	case SquidState::Leave:
		SOUND->Play("SquidExit");
		animRect->SetPosition(position + Vector2(10, 30) * totalSize);
		animRect->SetScale(Vector2(449, 606));
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Leave");
		if (animRect->GET_COMP(Animator)->GetEnd())
			state = SquidState::None;
		break;
	}

	dust->Update();
	animRect->Update();
	SQUIDBULLETMANAGER->Update();
}

void Squid::Render()
{
	if (state != SquidState::None)
	{
		animRect->Render();
		dust->Render();
	}
}

void Squid::GUI()
{
	string objName = "Squid";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		animRect->SetOutline(true);

		if (ImGui::InputFloat("Pos.x", (float*)&position.x, 1.0f, 100.0f))
			animRect->SetPosition(position);
		if (ImGui::InputFloat("Pos.y", (float*)&position.y, 1.0f, 100.0f))
			animRect->SetPosition(position);
		
		ImGui::InputFloat("AttackTime", &attackTime, 1.0f, 100.0f, "%0.1f");
		ImGui::InputFloat("Scale", &totalSize, 0.1f, 10.0f, "%0.2f");

		SQUIDBULLETMANAGER->GUI();

		ImGui::EndMenu();
	}
	else
	{
		animRect->SetOutline(false);
	}
}
