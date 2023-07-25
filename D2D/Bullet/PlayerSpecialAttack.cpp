#include "stdafx.h"
#include "PlayerSpecialAttack.h"

PlayerSpecialAttack::PlayerSpecialAttack(float bulletSpeed)
	: speed(bulletSpeed)
{
	animRect = make_shared<AnimationRect>(Vector2(), Vector2(159, 43), 0.0f, L"_Textures/PlayerBullet/weapon_peashot_EX_loop.png");
	animRect->AddAnimClip(make_shared<AnimationClip>(L"IntroA", L"_Textures/PlayerBullet/weapon_peashot_EX_intro.png", 3, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Main", L"_Textures/PlayerBullet/weapon_peashot_EX_loop.png", 8, false, true, 0.1));
	
	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// AddComponent
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void PlayerSpecialAttack::Init(Vector2 position, float rotation)
{
	runTime = 0.0f;
	animRect->SetPosition(position);
	animRect->SetRotation(rotation);
}

void PlayerSpecialAttack::Update()
{
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
//	cout << speed << '\n';
	animRect->Update();
}

void PlayerSpecialAttack::Render()
{
	animRect->Render();
}
