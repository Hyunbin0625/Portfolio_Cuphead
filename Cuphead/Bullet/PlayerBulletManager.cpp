#include "stdafx.h"
#include "PlayerBulletManager.h"

PlayerBulletManager::PlayerBulletManager(UINT totalBullet, float bulletSpeed, float speakerSpeed)
	: totalBullet(totalBullet), bulletSpeed(bulletSpeed), speakerSpeed(speakerSpeed)
{
	// �ʱ�ȭ
	time = 0;
	count = 0;
	totalSize = 1;

	bullets.resize(totalBullet);

	for (auto& bullet : bullets)
		bullet = make_shared<PlayerBullet>(bulletSpeed);
}

void PlayerBulletManager::CreateBullet()
{
	totalBullet *= 2;
	bullets.resize(totalBullet);

	for (int i = totalBullet / 2; i < totalBullet; ++i)
		bullets[i] = make_shared<PlayerBullet>(bulletSpeed);
}

void PlayerBulletManager::Init(Vector2 position, float rotation, float rebound)
{
//	if (count >= -1 && bCount == 0)
//		--count;
//	else if (bCount == 0)
//	{
//		bCount = 1;
//		count = 0;
//	}
//
//	if (count <= 1 && bCount == 1)
//		++count;
//	else if (bCount == 1)
//	{
//		bCount = 0;
//		count = 0;
//	}
	bullets[nextIndex]->Init(Vector2(position.x, position.y + count * rebound), rotation);
}

void PlayerBulletManager::IndexManagement()
{
	time += speakerSpeed * DELTA;

	// Loop�� 
	if (time >= totalBullet - 1)
	{
		if (bullets[0]->GetActivation() == true)	// 0�� Ȱ��ȭ �Ǿ� ���� ��
			CreateBullet();
		else
		{
			nextIndex = 0;
			time = 0.0f;
			lastIndex = -1;
		}
	}
	if ((int)time != lastIndex)
	{
		lastIndex = (int)time;
		bullets[(int)time]->SetActivation(true);
		++nextIndex;
	}
}

void PlayerBulletManager::Update()
{
	for (int i = 0; i < (int)totalBullet; ++i)
	{
		bullets[i]->SetTotalSize(totalSize);
		bullets[i]->Update();
	}
}

void PlayerBulletManager::Render()
{
	for (int i = 0; i < (int)totalBullet; ++i)
	{
		if (bullets[i]->GetActivation() == true)
			bullets[i]->Render();
	}
}