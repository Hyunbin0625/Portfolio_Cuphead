#include "stdafx.h"
#include "RibbyCoin.h"

RibbyCoin::RibbyCoin(float bulletSpeed)
	: speed(bulletSpeed)
{
	animRect = make_shared<AnimationRect>(Vector2(), Vector2(72, 74) * 0.75 * totalSize, 0.0f, L"_Textures/RibbyCroaks/tallfrog_slotman_coin.png");
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Coin", L"_Textures/RibbyCroaks/tallfrog_slotman_coin.png", 4, false, true, 0.1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// AddComponent
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::CIRCLE));
}

void RibbyCoin::Init(Vector2 position, float rotation)
{
	animRect->SetPosition(position);
	animRect->SetRotation(rotation);
	bActivation = true;
}

void RibbyCoin::Update()
{
	if (bActivation == true)
	{
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Coin");
		animRect->SetScale(Vector2(72, 74) * 0.75 * totalSize);

		animRect->Move(animRect->GetRightVector() * speed);

		// End
		if (animRect->GetPosition().y > CAMERA->GetPosition().y + WIN_DEFAULT_HEIGHT + 200 || animRect->GetPosition().y < CAMERA->GetPosition().y - 200
			|| animRect->GetPosition().x > CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH + 200 || animRect->GetPosition().x < CAMERA->GetPosition().x - 200)
			bActivation = false;
	}
	else
		animRect->SetPosition(Vector2(1000, -1000));

	animRect->Update();
}

void RibbyCoin::Render()
{
	animRect->Render();
}
