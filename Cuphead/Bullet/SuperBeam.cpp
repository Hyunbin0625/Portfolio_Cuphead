#include "stdafx.h"
#include "SuperBeam.h"

SuperBeam::SuperBeam()
{
	animRect = make_shared<AnimationRect>(Vector2(), Vector2(238, 177), 0.0f, L"_Textures/PlayerBullet/super_beam_end_R.png");

	// Intro
	animRect->AddAnimClip(make_shared<AnimationClip>(L"IntroR", L"_Textures/PlayerBullet/super_beam_intro_R.png", 9, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"IntroL", L"_Textures/PlayerBullet/super_beam_intro_L.png", 9, true, false, 0.1));
	// Loop
	animRect->AddAnimClip(make_shared<AnimationClip>(L"LoopR", L"_Textures/PlayerBullet/super_beam_loop_R.png", 4, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"LoopL", L"_Textures/PlayerBullet/super_beam_loop_L.png", 4, true, true, 0.1));
	// End
	animRect->AddAnimClip(make_shared<AnimationClip>(L"EndR", L"_Textures/PlayerBullet/super_beam_end_R.png", 7, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"EndL", L"_Textures/PlayerBullet/super_beam_end_L.png", 7, true, false, 0.1));
	
	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// AddComponent
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void SuperBeam::Init(Vector2 position, float totalSize, float deltaTime, float maxTime, bool bReverse)
{
	if (bReverse)	// LEFT
	{
		if (deltaTime >= 1.1f && deltaTime < 1.5f)	// 1.1~1.4
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"IntroL");
			animRect->SetScale(Vector2(1011, 271) * totalSize);
			animRect->SetPosition(Vector2(position.x - 560 * totalSize, position.y));
		}
		else if (deltaTime >= 1.1f && deltaTime < maxTime - 0.3f)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"LoopL");
			animRect->SetScale(Vector2(1018, 276) * totalSize);
			animRect->SetPosition(Vector2(position.x - 560 * totalSize, position.y));
		}
		else if (deltaTime >= 1.1f && deltaTime < maxTime)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"EndL");
			animRect->SetScale(Vector2(1016, 303) * totalSize);
			animRect->SetPosition(Vector2(position.x - 560 * totalSize, position.y));
		}
	}
	else	// Right
	{
		if (deltaTime >= 1.1f && deltaTime < 1.5f)	// 1.1~1.4
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"IntroR");
			animRect->SetScale(Vector2(1011, 271) * totalSize);
			animRect->SetPosition(Vector2(position.x + 560 * totalSize, position.y));
		}
		else if (deltaTime >= 1.1f && deltaTime < maxTime - 0.5f)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"LoopR");
			animRect->SetScale(Vector2(1018, 276) * totalSize);
			animRect->SetPosition(Vector2(position.x + 560 * totalSize, position.y));
		}
		else if (deltaTime >= 1.1f && deltaTime < maxTime)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"EndR");
			animRect->SetScale(Vector2(1016, 303) * totalSize);
			animRect->SetPosition(Vector2(position.x + 560 * totalSize, position.y));
		}
	}
}

void SuperBeam::Update()
{
	if (bSuperBeam == false)
		animRect->SetPosition(Vector2(-1000, -1000));
	animRect->Update();
}

void SuperBeam::Render()
{
	if (bSuperBeam)
		animRect->Render();
}
