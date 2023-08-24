#include "stdafx.h"
#include "RibbyFist.h"

RibbyFist::RibbyFist(float bulletSpeed)
	: speed(bulletSpeed)
{
	animRect = make_shared<AnimationRect>(Vector2(), Vector2(191, 120) * totalSize, 0.0f, L"_Textures/RibbyCroaks/shortfrog_fist_intro.png");
	animRect->AddAnimClip(make_shared<AnimationClip>(L"FistI", L"_Textures/RibbyCroaks/shortfrog_fist_intro.png", 3, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"FistL", L"_Textures/RibbyCroaks/shortfrog_fist_loop.png", 12, false, true, 0.1));
	
	animRect->AddAnimClip(make_shared<AnimationClip>(L"FistPI", L"_Textures/RibbyCroaks/shortfrog_fist_p_intro.png", 3, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"FistPL", L"_Textures/RibbyCroaks/shortfrog_fist_p_loop.png", 12, false, true, 0.1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// AddComponent
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void RibbyFist::Init(Vector2 position, float rotation)
{
	runTime = 0.0f;
	animRect->SetPosition(position);
	animRect->SetScale(Vector2(191, 120) * 0.85 * totalSize);
	animRect->SetRotation(rotation);
	bActivation = true;
}

void RibbyFist::Update()
{
	runTime += DELTA;
	if (runTime < 0.1f)
	{
		if (bParrySlap)
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"FistPI");
		else
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"FistI");
	}
	else
	{
		if (bParrySlap)
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"FistPL");
		else
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"FistL");
	}
	animRect->Move(animRect->GetRightVector() * speed);
	
	if (bActivation == true)
	{
		// End
		if (animRect->GetPosition().y > CAMERA->GetPosition().y + WIN_DEFAULT_HEIGHT + 200 || animRect->GetPosition().y < CAMERA->GetPosition().y - 200
			|| animRect->GetPosition().x > CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH + 200 || animRect->GetPosition().x < CAMERA->GetPosition().x - 200)
			bActivation = false;
	}
	else
		animRect->SetPosition(Vector2(1000, -1000));

	animRect->Update();
}

void RibbyFist::Render()
{
	animRect->Render();
}
