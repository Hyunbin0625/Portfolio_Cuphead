#include "stdafx.h"
#include "CroaksAttackManager.h"

CroaksAttackManager::CroaksAttackManager(UINT maxBullet, float bulletSpeed)
	: maxBullet(maxBullet), bulletSpeed(bulletSpeed)
{
	// ÃÊ±âÈ­
	currentIndex = 0;
	totalSize = 1.0f;
	this->maxBullet = maxBullet;
	
	totalIndex = maxBullet;
	bullets.resize(totalIndex);
	for (auto& bullet : bullets)
		bullet = make_shared<CroaksFirefly>(bulletSpeed);

	random_device random;
	mt = mt19937(random());
}

void CroaksAttackManager::CreateBullet(int addSize)
{
	totalIndex += addSize;
	bullets.resize(totalIndex);

	for (int i = totalIndex - addSize; i < totalIndex; ++i)
		bullets[i] = make_shared<CroaksFirefly>(bulletSpeed);
}

void CroaksAttackManager::InitSize()
{
	count = 0;
	uniform_int_distribution<int> randomSize(6, maxBullet);
	indexSize = randomSize(mt);
}

void CroaksAttackManager::InitPos(Vector2 position)
{
	currentIndex = -1;
	for (int i = 0; i < totalIndex; ++i)
	{
		if (!bullets[i]->GetActivation())
		{
			currentIndex = i;
			break;
		}
	}
	if (currentIndex == -1)
	{ 
		CreateBullet(indexSize);
		currentIndex = totalIndex - indexSize;
	}

	uniform_int_distribution<int> startPosX(100, 700);
	uniform_int_distribution<int> startPosY(500, 600);

	this->position = position;
	bullets[currentIndex]->Init(Vector2(position.x - 170 * totalSize, position.y + 165 * totalSize), Vector2(startPosX(mt), startPosY(mt)));
	++count;
}

void CroaksAttackManager::Update()
{
	for (auto& bullet : bullets)
	{
		bullet->SetTotalSize(totalSize);
		bullet->SetSpeed(bulletSpeed);

		if (bullet->GetActivation())
			bullet->Update();
	}
}

void CroaksAttackManager::Render()
{
	for (int i = 0; i < (int)totalIndex; ++i)
	{
		if (bullets[i]->GetActivation())
			bullets[i]->Render();
	}
}