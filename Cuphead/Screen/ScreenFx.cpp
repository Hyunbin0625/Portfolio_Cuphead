#include "stdafx.h"
#include "ScreenFx.h"

ScreenFx::ScreenFx()
{
	animRect = make_unique<AnimationRect>(CAMERA->GetPosition() + CENTER, Vector2(1280, 720), 0.0f, L"_Textures/ScreenFx/cuphead_screen_fx_01.png");

	animRect->AddAnimClip(make_shared<AnimationClip>(L"Screen01", L"_Textures/ScreenFx/cuphead_screen_fx_01.png", 10, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Screen02", L"_Textures/ScreenFx/cuphead_screen_fx_02.png", 10, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Screen03", L"_Textures/ScreenFx/cuphead_screen_fx_03.png", 10, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Screen04", L"_Textures/ScreenFx/cuphead_screen_fx_04.png", 10, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Screen05", L"_Textures/ScreenFx/cuphead_screen_fx_05.png", 10, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Screen06", L"_Textures/ScreenFx/cuphead_screen_fx_06.png", 10, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Screen07", L"_Textures/ScreenFx/cuphead_screen_fx_07.png", 10, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Screen08", L"_Textures/ScreenFx/cuphead_screen_fx_08.png", 10, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Screen09", L"_Textures/ScreenFx/cuphead_screen_fx_09.png", 10, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Screen10", L"_Textures/ScreenFx/cuphead_screen_fx_10.png", 10, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Screen11", L"_Textures/ScreenFx/cuphead_screen_fx_11.png", 10, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Screen12", L"_Textures/ScreenFx/cuphead_screen_fx_12.png", 10, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Screen13", L"_Textures/ScreenFx/cuphead_screen_fx_13.png", 7, false, false, 0.1));

	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	animRect->SetAnimator(animRect->GET_COMP(Animator));
}

ScreenFx::~ScreenFx() {}

void ScreenFx::Start()
{
	bActivation = true;
}

void ScreenFx::Update()
{
	if (bActivation)
	{
		if (clipCount == 0)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Screen01");
			if (animRect->GET_COMP(Animator)->GetEnd())
				++clipCount;
		}
		else if (clipCount == 1)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Screen02");
			if (animRect->GET_COMP(Animator)->GetEnd())
				++clipCount;
		}
		else if (clipCount == 2)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Screen03");
			if (animRect->GET_COMP(Animator)->GetEnd())
				++clipCount;
		}
		else if (clipCount == 3)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Screen04");
			if (animRect->GET_COMP(Animator)->GetEnd())
				++clipCount;
		}
		else if (clipCount == 4)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Screen05");
			if (animRect->GET_COMP(Animator)->GetEnd())
				++clipCount;
		}
		else if (clipCount == 5)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Screen06");
			if (animRect->GET_COMP(Animator)->GetEnd())
				++clipCount;
		}
		else if (clipCount == 6)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Screen07");
			if (animRect->GET_COMP(Animator)->GetEnd())
				++clipCount;
		}
		else if (clipCount == 7)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Screen08");
			if (animRect->GET_COMP(Animator)->GetEnd())
				++clipCount;
		}
		else if (clipCount == 8)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Screen09");
			if (animRect->GET_COMP(Animator)->GetEnd())
				++clipCount;
		}
		else if (clipCount == 9)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Screen10");
			if (animRect->GET_COMP(Animator)->GetEnd())
				++clipCount;
		}
		else if (clipCount == 10)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Screen11");
			if (animRect->GET_COMP(Animator)->GetEnd())
				++clipCount;
		}
		else if (clipCount == 11)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Screen12");
			if (animRect->GET_COMP(Animator)->GetEnd())
				++clipCount;
		}
		else
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Screen13");
			if (animRect->GET_COMP(Animator)->GetEnd())
				clipCount = 0;
		}
	}

	animRect->SetPosition(CAMERA->GetPosition() + CENTER);
	animRect->Update();
}

void ScreenFx::Render()
{
	if (bActivation)
		animRect->Render();
}
