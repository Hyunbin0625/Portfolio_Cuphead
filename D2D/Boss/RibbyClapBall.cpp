#include "stdafx.h"
#include "RibbyClapBall.h"

RibbyClapBall::RibbyClapBall(float bulletSpeed)
	: speed(bulletSpeed)
{
	animRect = make_shared<AnimationRect>(Vector2(), Vector2(118, 164) * totalSize, 0.0f, L"_Textures/RibbyCroaks/shorfrog_clap_ball.png");
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Ball", L"_Textures/RibbyCroaks/shorfrog_clap_ball.png", 3, false, true, 0.1));

	sfx = make_shared<AnimationRect>(Vector2(), Vector2(416, 176) * totalSize, 0.0f, L"_Textures/RibbyCroaks/shorfrog_clap_fx.png");
	sfx->AddAnimClip(make_shared<AnimationClip>(L"ClapFX", L"_Textures/RibbyCroaks/shorfrog_clap_fx.png", 7, false, false, 0.1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	sfx->AddComponent(make_shared<AnimatorComponent>(sfx->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));
	sfx->SetAnimator(sfx->GET_COMP(Animator));

	// AddComponent
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void RibbyClapBall::Init(Vector2 position, float rotation)
{
	runTime = 0.0f;
	animRect->SetPosition(position);
	animRect->SetRotation(rotation);
	bActivation = true;
}

void RibbyClapBall::Update()
{
	if (bActivation == true)
	{
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Ball");
		animRect->SetScale(Vector2(118, 164) * 0.75 * totalSize);

		animRect->Move(animRect->GetRightVector() * speed);
		// »óÇÏ
		if ((animRect->GetPosition().y + animRect->GetRightVector().y * animRect->GetScale().y / 2 > CAMERA->GetPosition().y + WIN_DEFAULT_HEIGHT)
			|| (animRect->GetPosition().y + animRect->GetRightVector().y * animRect->GetScale().y / 2 < CAMERA->GetPosition().y + 40))
		{
			animRect->SetRotation(-animRect->GetRotationDegree());

			sfx->GET_COMP(Animator)->ResetFrame();
			sfx->SetScale(Vector2(416, 176) * 0.70 * totalSize);
			sfx->SetPosition(animRect->GetPosition());
			if (animRect->GetRotationDegree() > 0.0f)
				sfx->SetRotation(180.0f);
			else
				sfx->SetRotation(0.0f);
		}

		// End
		if (animRect->GetPosition().y > CAMERA->GetPosition().y + WIN_DEFAULT_HEIGHT + 200 || animRect->GetPosition().y < CAMERA->GetPosition().y - 200
			|| animRect->GetPosition().x > CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH + 200 || animRect->GetPosition().x < CAMERA->GetPosition().x - 200)
			bActivation = false;
	}
	else
		animRect->SetPosition(Vector2(1000, -1000));

	if (sfx->GET_COMP(Animator)->GetEnd())
		sfx->SetPosition(Vector2(1000, -1000));

	animRect->Update();
	sfx->Update();
}

void RibbyClapBall::Render()
{
	animRect->Render();
	sfx->Render();
}
