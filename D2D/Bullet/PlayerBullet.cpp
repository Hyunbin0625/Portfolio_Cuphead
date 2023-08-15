#include "stdafx.h"
#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(float bulletSpeed)
	: speed(bulletSpeed)
{
	animRect = make_shared<AnimationRect>(Vector2(), Vector2(159, 43), 0.0f, L"_Textures/PlayerBullet/weapon_peashot_main.png");
	animRect->AddAnimClip(make_shared<AnimationClip>(L"IntroA", L"_Textures/PlayerBullet/weapon_peashot_intro_a.png", 3, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Main", L"_Textures/PlayerBullet/weapon_peashot_main.png", 6, false, true, 0.1));
	
	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// AddComponent
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void PlayerBullet::Init(Vector2 position, float rotation)
{
	bHit = true;
	runTime = 0.0f;
	animRect->SetPosition(position);
	animRect->SetRotation(rotation);
}

void PlayerBullet::Hit()
{
	bHit = false;
	time = runTime;
}

void PlayerBullet::Update()
{
	if (!bHit)
	{
		time += DELTA;
		if (time > 0.2f)
			bActivation = false;
	}

	runTime += 1 * DELTA;

	if (runTime < 0.1f)
	{
		animRect->SetScale(Vector2(60, 43) * totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"IntroA");
	}
	else
	{
		animRect->SetScale(Vector2(159, 43) * totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Main");
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
		animRect->SetPosition(Vector2(-500, -500));

	animRect->Update();
}

void PlayerBullet::Render()
{
	animRect->Render();
}
