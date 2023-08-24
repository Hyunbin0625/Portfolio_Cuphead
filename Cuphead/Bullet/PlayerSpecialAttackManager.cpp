#include "stdafx.h"
#include "PlayerSpecialAttackManager.h"

PlayerSpecialAttackManager::PlayerSpecialAttackManager(UINT totalBullet, float bulletSpeed)
	: totalBullet(totalBullet), bulletSpeed(bulletSpeed)
{
	// 초기화
	currentIndex = 0;
	totalSize = 1;

	bullets.resize(totalBullet);

	for (auto& bullet : bullets)
		bullet = make_shared<PlayerSpecialAttack>(bulletSpeed);
}

void PlayerSpecialAttackManager::CreateBullet()
{
	totalBullet *= 2;
	bullets.resize(totalBullet);

	for (int i = totalBullet / 2; i < totalBullet; ++i)
		bullets[i] = make_shared<PlayerSpecialAttack>(bulletSpeed);
}

void PlayerSpecialAttackManager::Init(Vector2 position, float rotation)
{
	this->position = position;
	this->rotation = rotation;
}

void PlayerSpecialAttackManager::IndexManagement()
{
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

void PlayerSpecialAttackManager::Update()
{
	for (int i = 0; i < (int)totalBullet; ++i)
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

void PlayerSpecialAttackManager::Render()
{
	for (int i = 0; i < (int)totalBullet; ++i)
	{
		if (bullets[i]->GetActivation() == true)
			bullets[i]->Render();
	}
}
