#include "stdafx.h"
#include "RibbyAttackManager.h"

// ManagerClass
RibbyAttackManager::RibbyAttackManager()
{
	random_device random;
	mt = mt19937(random());
}

RibbyAttackManager::~RibbyAttackManager() {}

void RibbyAttackManager::Init(UINT totalBullet, float bulletSpeed, Vector2 position, float rotation, int currentPhase)
{
	bEnd = false;
	currentIndex = 0;
	this->currentPhase = currentPhase;
	this->position = position;
	this->rotation = rotation;
	this->totalBullet = totalBullet;
	this->bulletSpeed = bulletSpeed;

	if (currentPhase == 1)
	{
		bullets.resize(totalBullet);

		for (auto& bullet : bullets)
			bullet = make_shared<RibbyFist>(bulletSpeed);
	}
	else if (currentPhase == 2)
	{
		balls.resize(totalBullet);
		for (auto& ball : balls)
			ball = make_shared<RibbyBall>(bulletSpeed);
	}
	else if (currentPhase == 3)
	{
		coins.resize(totalBullet);
		for (auto& coin : coins)
			coin = make_shared<RibbyCoin>(bulletSpeed);
	}
}

void RibbyAttackManager::InitBall()
{
	uniform_int_distribution<int> randomRotation(0, 1);
	if (randomRotation(mt))
		rotation = 65.0f;
	else
		rotation = -65.0f;

	if (!balls[currentIndex]->GetActivation())
		balls[currentIndex++]->Init(Vector2(position.x, position.y + rebound * count), rotation);

	if (currentIndex >= totalBullet)
	{
		currentIndex = 0;
		bEnd = true;
	}
}

void RibbyAttackManager::InitCoin(float rotation, Vector2 position)
{
	if (!coins[currentIndex]->GetActivation())
		coins[currentIndex++]->Init(position, rotation);

	if (currentIndex >= totalBullet)
	{
		currentIndex = 0;
		bEnd = true;
	}
}

void RibbyAttackManager::Update()
{
	if (currentPhase == 1 && !bEnd)
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
			rebound = 90.0f * totalSize;
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

	for (auto& ball : balls)
	{
		ball->SetTotalSize(totalSize);
		ball->SetSpeed(bulletSpeed);

		ball->Update();
	}

	for (auto& coin : coins)
	{
		coin->SetTotalSize(totalSize);
		coin->SetSpeed(bulletSpeed);

		coin->Update();
	}
}

void RibbyAttackManager::Render()
{
	for (auto& bullet : bullets)
	{
		if (bullet->GetActivation())
			bullet->Render();
	}
	for (auto& ball : balls)
	{
		if (ball->GetActivation())
			ball->Render();
	}
	for (auto& coin : coins)
	{
		if (coin->GetActivation())
			coin->Render();
	}
}