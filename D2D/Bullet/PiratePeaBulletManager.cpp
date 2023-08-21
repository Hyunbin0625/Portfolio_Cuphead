#include "stdafx.h"
#include "PiratePeaBulletManager.h"

PiratePeaBullet::PiratePeaBullet()
{
	animRect = make_shared<AnimationRect>(Vector2(), Vector2(62, 31), 0.0f, L"_Textures/Pirate/pirate_peaBullet_R.png");
	
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Idle", L"_Textures/Pirate/pirate_peaBullet_R.png", 4, true, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"PIdle", L"_Textures/Pirate/pirate_pink_peaBullet_R.png", 4, true, true, 0.1));

	animRect->AddAnimClip(make_shared<AnimationClip>(L"Death", L"_Textures/Pirate/pirate_peaBulletDeath.png", 5, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"PDeath", L"_Textures/Pirate/pirate_pink_peaBulletDeath.png", 5, false, false, 0.1));
	
	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// AddComponent
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::CIRCLE));
}

void PiratePeaBullet::Init(Vector2 position, float rotation, float speed, bool bParry)
{
	bActivation = true;
	bDeath = false;
	this->speed = speed;
	animRect->SetPosition(position);
	animRect->SetRotation(rotation);
	bParrySlap = bParry;
}

void PiratePeaBullet::Update()
{
	if (bDeath)
	{
		if (bParrySlap)
		{
			animRect->SetScale(Vector2(102, 106) * totalSize);
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"PDeath");
		}
		else
		{
			animRect->SetScale(Vector2(104, 104) * totalSize);
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Death");
		}
		if (animRect->GET_COMP(Animator)->GetEnd())
			bActivation = false;
	}
	else 
	{
		if (bParrySlap)
		{
			animRect->SetScale(Vector2(62, 30) * totalSize);
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"PIdle");
		}
		else
		{
			animRect->SetScale(Vector2(62, 31) * totalSize);
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Idle");
		}
	}
	if (!bDeath)
		animRect->Move(animRect->GetRightVector() * speed);

	animRect->Update();
}

void PiratePeaBullet::Render()
{
	animRect->Render();
}


// Manager Class
PiratePeaBulletManager::PiratePeaBulletManager()
{
	// 초기화
	currentIndex = 0;
	totalSize = 1.0f;

	bullets.resize(2);

	for (auto& bullet : bullets)
		bullet = make_shared<PiratePeaBullet>();

	random_device random;
	mt = mt19937(random());
}

PiratePeaBulletManager::~PiratePeaBulletManager() {}

void PiratePeaBulletManager::CreateBullet()
{
	bullets.resize(bullets.size() * 2);

	for (int i = bullets.size() / 2; i < bullets.size(); ++i)
		bullets[i] = make_shared<PiratePeaBullet>();
}

void PiratePeaBulletManager::Init(Vector2 position, float rotation, float speed)
{
	this->position = position;
	this->rotation = rotation;
	this->speed = speed;
}

void PiratePeaBulletManager::IndexManagement()
{
	uniform_int_distribution<int> randombParry(0, 1);
	bullets[currentIndex++]->Init(position, rotation, speed, randombParry(mt));

	// Loop시 
	if (currentIndex >= bullets.size())
	{

		if (bullets[0]->GetActivation() == true)
			CreateBullet();
		else
			currentIndex = 0;
	}
}

void PiratePeaBulletManager::Update()
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
		else
			bullets[i]->GetAnimRect()->SetPosition(Vector2(-1000, -1000));

		bullets[i]->Update();
	}
}

void PiratePeaBulletManager::Render()
{
	for (int i = 0; i < bullets.size(); ++i)
	{
		if (bullets[i]->GetActivation() == true)
			bullets[i]->Render();
	}
}