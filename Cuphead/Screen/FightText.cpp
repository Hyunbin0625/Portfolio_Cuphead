#include "stdafx.h"
#include "FightText.h"

FightText::FightText()
{
	animRect = make_unique<AnimationRect>(CAMERA->GetPosition() + CENTER, Vector2(1280, 720), 0.0f, L"_Textures/ScreenFx/level_text_rungun_Start.png");

	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunNGoS", L"_Textures/ScreenFx/level_text_rungun_Start.png", 7, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunNGoL", L"_Textures/ScreenFx/level_text_rungun_Loop.png", 4, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunNGoE", L"_Textures/ScreenFx/level_text_rungun_End.png", 3, false, false, 0.1));

	animRect->AddAnimClip(make_shared<AnimationClip>(L"GetReadyS", L"_Textures/ScreenFx/FightText_GetReady_Start.png", 21, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"GetReadyE", L"_Textures/ScreenFx/FightText_GetReady_End.png", 30, false, false, 0.1));

	animRect->AddAnimClip(make_shared<AnimationClip>(L"Bravo01", L"_Textures/ScreenFx/level_bravo_01.png", 13, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Bravo02", L"_Textures/ScreenFx/level_bravo_02.png", 13, false, false, 0.1));

	animRect->AddAnimClip(make_shared<AnimationClip>(L"KO", L"_Textures/ScreenFx/FightText_KO.png", 27, false, false, 0.1));

	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// Sounds
	SOUND->AddSound("RunNGo", L"_Sounds/sfx_level_announcer_0002_b.wav");

	SOUND->AddSound("Ready_A", L"_Sounds/sfx_level_announcer_ready_A.wav");
	SOUND->AddSound("Ready_B", L"_Sounds/sfx_level_announcer_ready_B.wav");

	SOUND->AddSound("Bravo", L"_Sounds/sfx_platforming_outro_bravo_c.wav");

	SOUND->AddSound("KnockoutAnnouncer", L"_Sounds/sfx_level_announcer_knockout_0004.wav");
	SOUND->AddSound("KnockoutBell", L"_Sounds/sfx_level_knockout_bell.wav");
	SOUND->AddSound("KnockoutBoom", L"_Sounds/sfx_level_knockout_boom_01.wav");


}

FightText::~FightText() {}

void FightText::Init(FightTextType type, bool bStart, bool bEnd)
{
	this->type = type;
	this->bStart = bStart;
	this->bEnd = bEnd;
}

void FightText::Update()
{
	switch (type)
	{
	case FightTextType::None:
		break;
	case FightTextType::RunNGun:
		if (bStart)
		{
			if (animCount == 0)
			{
				SOUND->SetVolume("RunNGo", 0.8f);
				SOUND->Play("RunNGo");
				animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunNGoS");
				if (animRect->GET_COMP(Animator)->GetEnd())
					++animCount;
			}
			else if (animCount == 1)
			{
				deltaTime += DELTA;
				animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunNGoL");
				if (deltaTime >= 0.8f)
				{
					++animCount;
					deltaTime = 0.0f;
				}
			}
			else
			{
				animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunNGoE");
				if (animRect->GET_COMP(Animator)->GetEnd())
				{
					animCount = 0;
					type = FightTextType::None;
				}
			}
		}
		else if(bEnd)
		{
			if (animCount == 0)
			{
				SOUND->SetVolume("Bravo", 0.8f);
				SOUND->Play("Bravo");
				animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Bravo01");
				if (animRect->GET_COMP(Animator)->GetEnd())
					++animCount;
			}
			else
			{
				animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Bravo02");
				if (animRect->GET_COMP(Animator)->GetEnd())
				{
					animCount = 0;
					type = FightTextType::None;
				}
			}
		}
		break;
	case FightTextType::Boss_A:
		if (bStart)
		{
			if (animCount == 0)
			{
				SOUND->SetVolume("Ready_A", 0.8f);
				SOUND->Play("Ready_A");
				animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"GetReadyS");
				if (animRect->GET_COMP(Animator)->GetEnd())
					++animCount;
			}
			else
			{
				animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"GetReadyE");
				if (animRect->GET_COMP(Animator)->GetEnd())
				{
					animCount = 0;
					type = FightTextType::None;
				}
			}
		}
		else if(bEnd)
		{
			SOUND->SetVolume("KnockoutAnnouncer", 0.8f);
			SOUND->SetVolume("KnockoutBell", 0.8f);
			SOUND->SetVolume("KnockoutBoom", 0.8f);
			SOUND->Play("KnockoutAnnouncer");
			SOUND->Play("KnockoutBell");
			SOUND->Play("KnockoutBoom");
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"KO");
			if (animRect->GET_COMP(Animator)->GetEnd())
				type = FightTextType::None;
		}
		break;
	case FightTextType::Boss_B:
		if (bStart)
		{
			if (animCount == 0)
			{
				SOUND->SetVolume("Ready_B", 0.8f);
				SOUND->Play("Ready_B");
				animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"GetReadyS");
				if (animRect->GET_COMP(Animator)->GetEnd())
					++animCount;
			}
			else
			{
				animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"GetReadyE");
				if (animRect->GET_COMP(Animator)->GetEnd())
				{
					animCount = 0;
					type = FightTextType::None;
				}
			}
		}
		else if (bEnd)
		{
			SOUND->SetVolume("KnockoutAnnouncer", 0.8f);
			SOUND->SetVolume("KnockoutBell", 0.8f);
			SOUND->SetVolume("KnockoutBoom", 0.8f);
			SOUND->Play("KnockoutAnnouncer");
			SOUND->Play("KnockoutBell");
			SOUND->Play("KnockoutBoom");
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"KO");
			if (animRect->GET_COMP(Animator)->GetEnd())
				type = FightTextType::None;
		}
		break;
	}

	if (type != FightTextType::None)
		animRect->SetPosition(CAMERA->GetPosition() + CENTER);
	else
		animRect->SetPosition(Vector2(-1000, -1000));
	animRect->Update();
}

void FightText::Render()
{
	if (type != FightTextType::None)
		animRect->Render();
}
