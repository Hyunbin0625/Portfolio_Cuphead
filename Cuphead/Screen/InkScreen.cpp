#include "stdafx.h"
#include "InkScreen.h"

InkScreen::InkScreen()
{
	animRectList.resize(16);

	for (auto& animRect : animRectList)
		animRect = make_shared<AnimationRect>();

	animRectList[0] = make_shared<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Textures/Pirate/pirate_squid_ink_screen_01.png");
	animRectList[0]->SetScale(Vector2(1280, 720) * 1.5f);
	animRectList[0]->AddAnimClip(make_shared<AnimationClip>(L"ScreenS", L"_Textures/Pirate/pirate_squid_ink_screen_01.png", 5, false, false, 0.1));
	animRectList[0]->AddAnimClip(make_shared<AnimationClip>(L"ScreenE", L"_Textures/Pirate/pirate_squid_ink_screen_01.png", 5, true, false, 0.1));

	animRectList[0]->AddComponent(make_shared<AnimatorComponent>(animRectList[0]->GetAnimClips()));
	animRectList[0]->SetAnimator(animRectList[0]->GET_COMP(Animator));

	for (int i = 1; i <= (animRectList.size() - 1) / 3; ++i)
	{
		animRectList[i] = make_shared<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Textures/Pirate/pirate_squid_ink_screen_a.png");

		animRectList[i]->AddAnimClip(make_shared<AnimationClip>(L"Ink", L"_Textures/Pirate/pirate_squid_ink_screen_a.png", 16, false, false, 0.13));

		animRectList[i]->AddComponent(make_shared<AnimatorComponent>(animRectList[i]->GetAnimClips()));
		animRectList[i]->SetAnimator(animRectList[i]->GET_COMP(Animator));
	}

	for (int i = (animRectList.size() - 1) / 3 + 1; i <= (animRectList.size() - 1) / 3 * 2; ++i)
	{
		animRectList[i] = make_shared<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Textures/Pirate/pirate_squid_ink_screen_b.png");

		animRectList[i]->AddAnimClip(make_shared<AnimationClip>(L"Ink", L"_Textures/Pirate/pirate_squid_ink_screen_b.png", 20, false, false, 0.13));

		animRectList[i]->AddComponent(make_shared<AnimatorComponent>(animRectList[i]->GetAnimClips()));
		animRectList[i]->SetAnimator(animRectList[i]->GET_COMP(Animator));
	}

	for (int i = (animRectList.size() - 1) / 3 * 2 + 1; i < animRectList.size(); ++i)
	{
		animRectList[i] = make_shared<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Textures/Pirate/pirate_squid_ink_screen_e.png");

		animRectList[i]->AddAnimClip(make_shared<AnimationClip>(L"Ink", L"_Textures/Pirate/pirate_squid_ink_screen_e.png", 10, false, false, 0.13));

		animRectList[i]->AddComponent(make_shared<AnimatorComponent>(animRectList[i]->GetAnimClips()));
		animRectList[i]->SetAnimator(animRectList[i]->GET_COMP(Animator));
	}

	random_device random;
	mt = mt19937(random());

	// Sounds
	SOUND->AddSound("SquidBlackout", L"_Sounds/sfx_pirate_squid_blackout_screen.wav");
}

InkScreen::~InkScreen() {}

void InkScreen::Init(float duration)
{
	this->duration = duration;

	if (!bActivation)
	{
		SOUND->Play("SquidBlackout");
		uniform_real_distribution<float> randomScale(MScale.x, MScale.y);
		uniform_real_distribution<float> randomPosX(CAMERA->GetPosition().x, CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH);
		uniform_real_distribution<float> randomPosY(CAMERA->GetPosition().y, CAMERA->GetPosition().y + WIN_DEFAULT_HEIGHT);

		for (int i = 1; i <= (animRectList.size() - 1) / 3; ++i)
		{
			animRectList[i]->SetScale(Vector2(170, 778) * randomScale(mt));
			animRectList[i]->SetPosition(Vector2(randomPosX(mt), randomPosY(mt)));
		}

		for (int i = (animRectList.size() - 1) / 3 + 1; i <= (animRectList.size() - 1) / 3 * 2; ++i)
		{
			animRectList[i]->SetScale(Vector2(253, 777) * randomScale(mt));
			animRectList[i]->SetPosition(Vector2(randomPosX(mt), randomPosY(mt)));
		}

		for (int i = (animRectList.size() - 1) / 3 * 2 + 1; i < animRectList.size(); ++i)
		{
			animRectList[i]->SetScale(Vector2(225, 218) * randomScale(mt));
			animRectList[i]->SetPosition(Vector2(randomPosX(mt), randomPosY(mt)));
		}

		for (int i = 1; i < animRectList.size(); ++i)
		{
			animRectList[i]->GET_COMP(Animator)->ResetFrame();
			animRectList[i]->GET_COMP(Animator)->SetCurrentAnimClip(L"Ink");
		}

		animRectList[0]->SetPosition(CAMERA->GetPosition() + CENTER);
		animRectList[0]->GET_COMP(Animator)->ResetFrame();
		animRectList[0]->GET_COMP(Animator)->SetCurrentAnimClip(L"ScreenS");
	}

	bActivation = true;
	time = 0.0f;
}

void InkScreen::Update()
{
	if (bActivation)
	{
		time += DELTA;

		if (time >= duration)
		{
			animRectList[0]->GET_COMP(Animator)->SetCurrentAnimClip(L"ScreenE");
			if (animRectList[0]->GET_COMP(Animator)->GetEnd())
			{
				bActivation = false;
				for (auto& animRect : animRectList)
					animRect->SetPosition(Vector2(1000, -1000));
			}
		}

		for (int i = 1; i < animRectList.size(); ++i)
		{
			if (animRectList[i]->GET_COMP(Animator)->GetEnd())
				animRectList[i]->SetPosition(Vector2(1000, -1000));
		}

		for (auto& animRect : animRectList)
			animRect->Update();
	}
}

void InkScreen::Render()
{
	if (bActivation)
	{
		for (auto& animRect : animRectList)
			animRect->Render();
	}
}
