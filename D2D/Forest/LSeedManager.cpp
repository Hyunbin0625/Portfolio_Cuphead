#include "stdafx.h"
#include "LSeedManager.h"

LobberSeed::LobberSeed(float bulletSpeed)
	: speed(bulletSpeed)
{
	animRect = make_shared<AnimationRect>(Vector2(), Vector2(70, 73), 0.0f, L"_Textures/Enemy/lobber_seed.png");
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Seed", L"_Textures/Enemy/lobber_seed.png", 8, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"ExplosionR", L"_Textures/Enemy/lobber_explosion_R.png", 23, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"ExplosionL", L"_Textures/Enemy/lobber_explosion_L.png", 23, true, false, 0.1));
	
	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// AddComponent
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void LobberSeed::Init(Vector2 position, float rotation, float playerX)
{
	G = 0;
	jumpSpeed = 500.0f;
	cout << playerX << '\n';
	cout << position.x << '\n';

	space = playerX - position.x;
	bGround = false;

	this->playerX = playerX;
	animRect->SetPosition(position);
	animRect->SetRotation(rotation);
}

void LobberSeed::Update()
{
	// Animation
	if (bGround)
	{
		animRect->SetScale(Vector2(370, 443) * 0.5 * totalSize);
		animRect->SetPosition(Vector2(position.x, position.y + 70 * totalSize));
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"ExplosionR");
		if (animRect->GET_COMP(Animator)->GetEnd())
		{
			bActivation = false;
			animRect->SetPosition(Vector2(1000, -1000));
		}
	}
	else
	{
		// time, G
		G += 9.8 * DELTA;
		jumpSpeed -= G;

		animRect->SetScale(Vector2(70, 73) * totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Seed");
		this->position = animRect->GetPosition();
		// Move
	//	cout << space << '\n';
	//	cout << jumpSpeed << '\n';

		animRect->Move(Vector2(space, jumpSpeed));
	}
	animRect->Update();
}

void LobberSeed::Render()
{
	animRect->Render();
}

// ManagerClass
LSeedManager::LSeedManager(UINT totalBullet, float bulletSpeed)
	: totalBullet(totalBullet), bulletSpeed(bulletSpeed)
{
	// 초기화
	currentIndex = 0;
	totalSize = 1.0f;

	bullets.resize(totalBullet);

	for (auto& bullet : bullets)
		bullet = make_shared<LobberSeed>(bulletSpeed);
}

void LSeedManager::CreateBullet()
{
	totalBullet *= 2;
	bullets.resize(totalBullet);

	for (int i = totalBullet / 2; i < totalBullet; ++i)
		bullets[i] = make_shared<LobberSeed>(bulletSpeed);
}

void LSeedManager::Init(Vector2 position, float rotation, float playerX)
{
	this->playerX = playerX;
	this->position = position;
	this->rotation = rotation;
}

void LSeedManager::IndexManagement()
{
	bullets[currentIndex]->Init(position, rotation, playerX);
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

void LSeedManager::Update()
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

void LSeedManager::Render()
{
	for (int i = 0; i < (int)totalBullet; ++i)
	{
		if (bullets[i]->GetActivation() == true)
			bullets[i]->Render();
	}
}
