#include "stdafx.h"
#include "RibbyFistManager.h"

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


// ManagerClass
RibbyFistManager::RibbyFistManager(UINT totalBullet, float bulletSpeed, float rebound)
	: totalBullet(totalBullet), bulletSpeed(bulletSpeed), rebound(rebound)
{
	// 초기화
	currentIndex = 0;
	totalSize = 1.0f;

	bullets.resize(totalBullet);

	for (auto& bullet : bullets)
		bullet = make_shared<RibbyFist>(bulletSpeed);

	random_device random;
	mt = mt19937(random());
}

void RibbyFistManager::Init(Vector2 position, float rotation)
{
	bEnd = false;
	this->position = position;
	this->rotation = rotation;
}

void RibbyFistManager::Update()
{
	if (!bEnd)
	{
		time += DELTA;
		if (time >= 0.7f)
		{
			// 0~2마다 parrySlap 지정
			if (currentIndex % 3 == 0)
			{
				uniform_int_distribution<int> parrySlap(0, 2);
				parrySlapIndex = parrySlap(mt);
			}
			// 같을 때 set
			if (currentIndex % 3 == parrySlapIndex)
			{
				bullets[currentIndex]->SetParrySlap(true);
			}
			else
				bullets[currentIndex]->SetParrySlap(false);
			if (currentIndex % 6 == 0)
			{
				uniform_int_distribution<int> randomCount(0, 2);
				count = randomCount(mt);
			}

			bullets[currentIndex++]->Init(Vector2(position.x, position.y + rebound * count), rotation);

			if (bUp)
				++count;
			else
				--count;
			if (count > 2)
			{
				bUp = false;
				count = 1;
			}
			else if (count < 0)
			{
				bUp = true;
				count = 1;
			}
		
			time = 0.0f;
		}

		if (currentIndex >= totalBullet)
		{
			currentIndex = 0;
			bEnd = true;
		}
	}

	for (auto& bullet : bullets)
	{
		bullet->SetTotalSize(totalSize);
		bullet->SetSpeed(bulletSpeed);

		bullet->Update();
	}
}

void RibbyFistManager::Render()
{
	for (int i = 0; i < (int)totalBullet; ++i)
	{
		if (bullets[i]->GetActivation() == true)
			bullets[i]->Render();
	}
}