#include "stdafx.h"
#include "PlayerBulletManager.h"

PlayerBulletManager::PlayerBulletManager(UINT totalBullet, float bulletSpeed, float speakerSpeed)
	: totalBullet(totalBullet), bulletSpeed(bulletSpeed), speakerSpeed(speakerSpeed)
{
	// 초기화
	time = 0;
	count = 0;
	totalSize = 1;

	bullets.resize(totalBullet);
	activation.assign(this->totalBullet, bool());

	for (auto& bullet : bullets)
		bullet = make_shared<PlayerBullet>(bulletSpeed);
	for (auto active : activation)
		active = 0;
}

void PlayerBulletManager::CreateBullet()
{
	totalBullet *= 2;
	bullets.resize(totalBullet);
	activation.resize(totalBullet, bool());

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
	if ((int)time != lastIndex)
	{
		lastIndex = (int)time;
		activation[time] = 1;
		++nextIndex;
	}
}

void PlayerBulletManager::Update()
{
//	cout << time << '\n';
	for (int i = 0; i < (int)totalBullet; ++i)
	{
		bullets[i]->SetTotalSize(totalSize);
		if (activation[i] == true)
		{
			bullets[i]->Update();

			// 	// End
			if (bullets[i]->GetAnimRect()->GetPosition().y > CAMERA->GetPosition().y + WIN_DEFAULT_HEIGHT + 200 || bullets[i]->GetAnimRect()->GetPosition().y < CAMERA->GetPosition().y - 200
				|| bullets[i]->GetAnimRect()->GetPosition().x > CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH + 200 || bullets[i]->GetAnimRect()->GetPosition().x < CAMERA->GetPosition().x - 200)
			{
				activation[i] = false;
				bullets[i]->GetAnimRect()->SetPosition(Vector2(-500, -500));
			}
		}
	}

	// Loop시 
	if ((UINT)time >= totalBullet - 1)
	{
		if (activation[0] == 1)	// 0이 활성화 되어 있을 때
			CreateBullet();
		else
		{
			nextIndex = 0;
			time = 0.0f;
			lastIndex = -1;
		}
	}
}

void PlayerBulletManager::Render()
{
	for (int i = 0; i < (int)totalBullet; ++i)
	{
		if (activation[i] == true)
			bullets[i]->Render();
	}
}
