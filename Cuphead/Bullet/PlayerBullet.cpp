#include "stdafx.h"
#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(float bulletSpeed)
	: speed(bulletSpeed)
{
	animRect = make_shared<AnimationRect>(Vector2(), Vector2(159, 43), 0.0f, L"_Textures/PlayerBullet/weapon_peashot_main.png");
	animRect->AddAnimClip(make_shared<AnimationClip>(L"IntroA", L"_Textures/PlayerBullet/weapon_peashot_intro_a.png", 3, false, false, 0.05));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Loop", L"_Textures/PlayerBullet/weapon_peashot_main.png", 6, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"End", L"_Textures/PlayerBullet/weapon_peashot_death.png", 6, false, false, 0.1));
	
	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// AddComponent
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void PlayerBullet::Init(Vector2 position, float rotation)
{
	bHit = false;
	time = 1.0f;
	animCount = 0;
	animRect->SetPosition(position);
	animRect->SetRotation(rotation);
}

void PlayerBullet::Hit()
{
	bHit = true;
	time = 0.0f;
}

void PlayerBullet::Update()
{	
	if (bActivation)
	{
		if (bHit)
		{
			time += DELTA;
			if (time > 0.2f)
			{
			//	animRect->SetPosition(animRect->GetPosition() + Vector2(100, 0) * totalSize);
				animRect->SetScale(Vector2(263, 283) * totalSize);
				animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"End");
				if (animRect->GET_COMP(Animator)->GetEnd())
					bActivation = false;
			}
		}
		else if (animCount == 0)
		{
			animRect->SetScale(Vector2(60, 43) * totalSize);
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"IntroA");
			if (animRect->GET_COMP(Animator)->GetEnd())
				++animCount;
		}
		else
		{
			animRect->SetScale(Vector2(159, 43) * totalSize);
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Loop");
		}

		if ((bHit && time <= 0.2f) || !bHit)
			animRect->Move(animRect->GetRightVector() * speed);

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
	if (bActivation)
		animRect->Render();
}
