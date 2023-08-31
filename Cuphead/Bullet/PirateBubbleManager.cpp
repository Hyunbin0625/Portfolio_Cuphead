#include "stdafx.h"
#include "PirateBubbleManager.h"

PirateBubble::PirateBubble()
{
	animRect = make_shared<AnimationRect>(Vector2(), Vector2(105, 103), 0.0f, L"_Textures/Pirate/pirate_whaleboat_bubble_start.png");

	animRect->AddAnimClip(make_shared<AnimationClip>(L"Intro", L"_Textures/Pirate/pirate_whaleboat_bubble_start.png", 3, false, false, 0.12));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Loop", L"_Textures/Pirate/pirate_whaleboat_bubble_loop.png", 13, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Death", L"_Textures/Pirate/pirate_whaleboat_bubble_death.png", 5, false, false, 0.1));
	
	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));

	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// AddComponent
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::CIRCLE));
}

void PirateBubble::Init(Vector2 position, float rotation, float totalSize, float speed, float range)
{
	this->position = position;
	this->totalSize = totalSize;
	this->speed = speed;
	this->range = range;
	animRect->SetRotation(rotation);

	bActivation = true;
	bEnd = false;
	count = 0;

	animRect->GET_COMP(Animator)->ResetFrame();
}

void PirateBubble::Update()
{
	if (bActivation)
	{
		if (count == 0)
		{
			animRect->SetScale(Vector2(105, 103) * 0.7f * totalSize);
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Intro");
			if (animRect->GET_COMP(Animator)->GetEnd())
				++count;
		}
		else if (bEnd)
		{
			animRect->SetScale(Vector2(366, 400) * 0.7f * totalSize);
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Death");
			if (animRect->GET_COMP(Animator)->GetEnd())
				bActivation = false;
		}
		else if (count == 1)
		{
			animRect->SetScale(Vector2(105, 103) * 0.7f * totalSize);
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Loop");
		}

		if (!bEnd)
		{
			rotate -= 4.0f * DELTA;
			if (rotate >= 360.0f)
				rotate = 0.0f;

			rotatePos.x = position.x + range * cos(rotate);
			rotatePos.y = position.y + range * sin(rotate);

			animRect->SetPosition(rotatePos);
			position.x -= speed * DELTA;
		}

		// End
		if (animRect->GetPosition().x + animRect->GetScale().x <= CAMERA->GetPosition().x)
			bActivation = false;
	}

	animRect->Update();
}

void PirateBubble::Render()
{
	if (bActivation)
		animRect->Render();
}


// Manager Class
PirateBubbleManager::PirateBubbleManager()
{
	bullets.resize(2);

	for (auto& bullet : bullets)
		bullet = make_shared<PirateBubble>();
}

PirateBubbleManager::~PirateBubbleManager() {}

void PirateBubbleManager::CreateBullet()
{
	bullets.resize(bullets.size() * 2);

	for (int i = bullets.size() / 2; i < bullets.size(); ++i)
		bullets[i] = make_shared<PirateBubble>();
}

void PirateBubbleManager::IndexManagement(Vector2 position, float rotation, float totalSize, float speed, float range)
{
	bullets[currentIndex++]->Init(position, rotation, totalSize, speed, range);

	// Loop½Ã 
	if (currentIndex >= bullets.size())
	{
		if (bullets[0]->GetActivation() == true)
			CreateBullet();
		else
			currentIndex = 0;
	}
}

void PirateBubbleManager::Update()
{
	for (auto& bullet : bullets)
		bullet->Update();
}

void PirateBubbleManager::Render()
{
	for (auto& bullet : bullets)
		bullet->Render();
}