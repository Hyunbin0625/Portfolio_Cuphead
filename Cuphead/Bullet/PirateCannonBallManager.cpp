#include "stdafx.h"
#include "PirateCannonBallManager.h"

PirateCannonBall::PirateCannonBall()
{
	animRect = make_shared<AnimationRect>(Vector2(), Vector2(197, 101), 0.0f, L"_Textures/Pirate/pirate_boatCannonball.png");
	SFX = make_shared<AnimationRect>(Vector2(), Vector2(248, 317), 0.0f, L"_Textures/Pirate/pirate_CannonDust.png");
	collisionRect = make_shared<ColorRect>(Vector2(), Vector2(87, 87), 0.0f, GREEN);
	
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Idle", L"_Textures/Pirate/pirate_boatCannonball.png", 4, false, true, 0.1));
	SFX->AddAnimClip(make_shared<AnimationClip>(L"Dust", L"_Textures/Pirate/pirate_CannonDust.png", 14, false, false, 0.1));
	
	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	SFX->AddComponent(make_shared<AnimatorComponent>(SFX->GetAnimClips()));

	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));
	SFX->SetAnimator(SFX->GET_COMP(Animator));

	// AddComponent
	collisionRect->AddComponent(make_shared<ColliderComponent>(ColliderType::CIRCLE));
}

void PirateCannonBall::Init(Vector2 position, float rotation, float speed)
{
	bActivation = true;
	bSFX = true;
	this->speed = speed;
	animRect->SetPosition(position);
	SFX->SetPosition(position + Vector2(-100, -20) * totalSize);
	animRect->SetRotation(rotation);
	SFX->SetRotation(rotation);
	SFX->GET_COMP(Animator)->ResetFrame();
}

void PirateCannonBall::Update()
{
	if (bActivation)
	{
		animRect->SetScale(Vector2(197, 101) * totalSize);
		SFX->SetScale(Vector2(248, 317) * totalSize);

		collisionRect->SetPosition(animRect->GetPosition() + Vector2(-48, 0) * totalSize);

		animRect->Move(-animRect->GetRightVector() * speed);
		if (bSFX)
			SFX->Move(-SFX->GetRightVector() * speed);
		if (SFX->GET_COMP(Animator)->GetEnd())
			bSFX = false;
	}
	else
	{
		animRect->SetPosition(Vector2(-1000, -1000));
		SFX->SetPosition(Vector2(-1000, -1000));
	}

	animRect->Update();
	SFX->Update();
	collisionRect->Update();
}

void PirateCannonBall::Render()
{
	if (bActivation)
	{
	//	collisionRect->Render();
		animRect->Render();
	}
	if (bSFX)
		SFX->Render();
}


// Manager Class
PirateCannonBallManager::PirateCannonBallManager()
{
	// 초기화
	currentIndex = 0;
	totalSize = 1.0f;

	bullets.resize(2);

	for (auto& bullet : bullets)
		bullet = make_shared<PirateCannonBall>();
}

PirateCannonBallManager::~PirateCannonBallManager() {}

void PirateCannonBallManager::CreateBullet()
{
	bullets.resize(bullets.size() * 2);

	for (int i = bullets.size() / 2; i < bullets.size(); ++i)
		bullets[i] = make_shared<PirateCannonBall>();
}

void PirateCannonBallManager::Init(Vector2 position, float rotation, float speed)
{
	this->position = position;
	this->rotation = rotation;
	this->speed = speed;
}

void PirateCannonBallManager::IndexManagement()
{
	bullets[currentIndex++]->Init(position, rotation, speed);

	// Loop시 
	if (currentIndex >= bullets.size())
	{
		if (bullets[0]->GetActivation() == true)
			CreateBullet();
		else
			currentIndex = 0;
	}
}

void PirateCannonBallManager::Update()
{
	for (int i = 0; i < bullets.size(); ++i)
	{
		bullets[i]->SetTotalSize(totalSize);
		if (bullets[i]->GetActivation() == true)
		{
			// End
			if (bullets[i]->GetAnimRect()->GetPosition().y > CAMERA->GetPosition().y + WIN_DEFAULT_HEIGHT + 200 || bullets[i]->GetAnimRect()->GetPosition().y < CAMERA->GetPosition().y - 200
				|| bullets[i]->GetAnimRect()->GetPosition().x > CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH + 200 || bullets[i]->GetAnimRect()->GetPosition().x < CAMERA->GetPosition().x - 200)
				bullets[i]->SetActivation(false);
		}

		bullets[i]->Update();
	}
}

void PirateCannonBallManager::Render()
{
	for (auto& bullet : bullets)
		bullet->Render();
}