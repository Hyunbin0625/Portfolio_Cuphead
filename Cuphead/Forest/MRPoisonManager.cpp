#include "stdafx.h"
#include "MRPoisonManager.h"

MushroomPoison::MushroomPoison(float bulletSpeed)
	: speed(bulletSpeed)
{
	animRect = make_shared<AnimationRect>(Vector2(), Vector2(91, 84), 0.0f, L"_Textures/Enemy/mushroom_poison_cloud.png");
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Poison", L"_Textures/Enemy/mushroom_poison_cloud.png", 12, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"PoisonP", L"_Textures/Enemy/mushroom_poison_cloud_pink.png", 12, false, true, 0.1));
	
	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// AddComponent
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void MushroomPoison::Init(Vector2 position, float rotation)
{
	animRect->SetPosition(position);
	animRect->SetRotation(rotation);
}

void MushroomPoison::Update()
{
	animRect->SetScale(Vector2(91, 84) * totalSize);
	if (bParrySlap)
	{
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"PoisonP");
	}
	else
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Poison");

	animRect->Move(animRect->GetRightVector() * speed);

	animRect->Update();
}

void MushroomPoison::Render()
{
	animRect->Render();
}

// ManagerClass
MRPoisonManager::MRPoisonManager(UINT totalBullet, float bulletSpeed)
	: totalBullet(totalBullet), bulletSpeed(bulletSpeed)
{
	// 초기화
	currentIndex = 0;
	totalSize = 1.0f;

	bullets.resize(totalBullet);

	for (auto& bullet : bullets)
		bullet = make_shared<MushroomPoison>(bulletSpeed);

	random_device random;
	mt = mt19937(random());
}

void MRPoisonManager::CreateBullet()
{
	totalBullet *= 2;
	bullets.resize(totalBullet);

	for (int i = totalBullet / 2; i < totalBullet; ++i)
		bullets[i] = make_shared<MushroomPoison>(bulletSpeed);
}

void MRPoisonManager::Init(Vector2 position, float rotation)
{
	this->position = position;
	this->rotation = rotation;
}

void MRPoisonManager::IndexManagement()
{
	uniform_int_distribution<int> parrySlap(0, 1);

	bullets[currentIndex]->SetParrySlap(parrySlap(mt));
	bullets[currentIndex]->Init(position, rotation);
	bullets[currentIndex++]->SetActivation(true);

	// Loop시 
	if (currentIndex > totalBullet - 1)
	{
		if (bullets[0]->GetActivation() == true)	// 0이 활성화 되어 있을 때
			CreateBullet();
		else
			currentIndex = 0;
	}
}

void MRPoisonManager::Update()
{
	for (int i = 0; i < (int)totalBullet; ++i)
	{
		bullets[i]->SetTotalSize(totalSize);
		bullets[i]->SetSpeed(bulletSpeed);
		if (bullets[i]->GetActivation() == true)
		{
			// End
			if (bullets[i]->GetAnimRect()->GetPosition().y > CAMERA->GetPosition().y + WIN_DEFAULT_HEIGHT + 200 || bullets[i]->GetAnimRect()->GetPosition().y < CAMERA->GetPosition().y - 200
				|| bullets[i]->GetAnimRect()->GetPosition().x > CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH + 200 || bullets[i]->GetAnimRect()->GetPosition().x < CAMERA->GetPosition().x - 200)
				bullets[i]->SetActivation(false);
		}
		else
			bullets[i]->GetAnimRect()->SetPosition(Vector2(1000, -1000));

		bullets[i]->Update();
	}
}

void MRPoisonManager::Render()
{
	for (int i = 0; i < (int)totalBullet; ++i)
	{
		if (bullets[i]->GetActivation() == true)
			bullets[i]->Render();
	}
}
