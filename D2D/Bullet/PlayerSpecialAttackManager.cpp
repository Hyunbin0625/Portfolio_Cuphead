#include "stdafx.h"
#include "PlayerSpecialAttackManager.h"

PlayerSpecialAttackManager::PlayerSpecialAttackManager(UINT totalBullet, float bulletSpeed)
	: totalBullet(totalBullet), bulletSpeed(bulletSpeed)
{
	// 초기화
	currentIndex = 0;
	totalSize = 3;

//	bullets.assign(totalBullet, make_shared<PlayerSpecialAttack>());
	bullets.resize(totalBullet);
	activation.assign(totalBullet, bool());

	for (auto& bullet : bullets)
		bullet = make_shared<PlayerSpecialAttack>(bulletSpeed);
	for (auto active : activation)
		active = 0;
}

void PlayerSpecialAttackManager::CreateBullet()
{
	totalBullet *= 2;
	bullets.resize(totalBullet, make_shared<PlayerSpecialAttack>(bulletSpeed));
	activation.resize(totalBullet, bool());
}

void PlayerSpecialAttackManager::Init(Vector2 position, float rotation)
{
	this->position = position;
	this->rotation = rotation;
}

void PlayerSpecialAttackManager::IndexManagement()
{
	bullets[currentIndex]->Init(position, rotation);
	activation[currentIndex++] = true;

	// Loop시 
	if (currentIndex > totalBullet - 1)
	{
		if (activation[0] == true)	// 0이 활성화 되어 있을 때
			CreateBullet();
		else
		{
			currentIndex = 0;
		}
	}
}

void PlayerSpecialAttackManager::Update()
{
	for (int i = 0; i < (int)totalBullet; ++i)
	{
		bullets[i]->SetTotalSize(totalSize);
		if (activation[i] == true)
		{
			bullets[i]->Update();

			// 	// End
			if (bullets[i]->GetAnimRect()->GetPosition().y > WIN_DEFAULT_HEIGHT + 200 || bullets[i]->GetAnimRect()->GetPosition().y < -200
				|| bullets[i]->GetAnimRect()->GetPosition().x > WIN_DEFAULT_WIDTH + 200 || bullets[i]->GetAnimRect()->GetPosition().x < -200)
			{
				activation[i] = false;
				bullets[i]->GetAnimRect()->SetPosition(Vector2(-1000, -1000));
			}
		}
	}
}

void PlayerSpecialAttackManager::Render()
{
	for (int i = 0; i < (int)totalBullet; ++i)
	{
		if (activation[i] == true)
			bullets[i]->Render();
	}
}
