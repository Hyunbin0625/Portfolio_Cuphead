#include "stdafx.h"
#include "PlayerBulletManager.h"

PlayerBulletManager::PlayerBulletManager(UINT totalBullet, float bulletSpeed, float speakerSpeed)
	: totalBullet(totalBullet), bulletSpeed(bulletSpeed), speakerSpeed(speakerSpeed)
{
	// 초기화
	time = 0;
	count = 1;
	totalSize = 1;

	bullets.assign(this->totalBullet, make_shared<PlayerBullet>());
	activation.assign(this->totalBullet, bool());

	for (auto& bullet : bullets)
		bullet = make_shared<PlayerBullet>(bulletSpeed);
	for (auto active : activation)
		active = 0;
}

void PlayerBulletManager::CreateBullet()
{
	vector<shared_ptr<PlayerBullet>> tempBullets;
	vector<bool> tempActivation;
	tempBullets.assign(totalBullet * 2, make_shared<PlayerBullet>());
	tempActivation.assign(totalBullet * 2, bool());
	for (int i = 0; i < (int)totalBullet; ++i)
	{
		tempBullets[i] = bullets[i];
		tempActivation[i] = activation[i];
	}

	totalBullet *= 2;
	bullets.assign(totalBullet, make_shared<PlayerBullet>());
	activation.assign(totalBullet, bool());

	for (auto& bullet : bullets)
		bullet = make_shared<PlayerBullet>(bulletSpeed);
	for (auto active : activation)
		active = 0;

	for (int i = 0; i < (int)totalBullet / 2; ++i)
	{
		bullets[i] = tempBullets[i];
		activation[i] = tempActivation[i];
	}
}

void PlayerBulletManager::Init(Vector2 position, float rotation, float rebound)
{
	this->position = Vector2(position.x, position.y + count * rebound);

	if (count >= -1 && bCount == 0)
	{
		--count;
		cout << "감소 : " << count << ", " << bCount << '\n';
	}
	else
	{
		bCount = 1;
		count = 0;
	}

	if (count <= 1 && bCount == 1)
	{
		++count;
		cout << "증가 : " << count << '\n';
	}
	else
	{
		bCount = 0;
		count = 0;
	}
	
	bullets[nextIndex]->Init(this->position, rotation);
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
			if (bullets[i]->GetAnimRect()->GetPosition().y > WIN_DEFAULT_HEIGHT + 200 || bullets[i]->GetAnimRect()->GetPosition().y < -200
				|| bullets[i]->GetAnimRect()->GetPosition().x > WIN_DEFAULT_WIDTH + 200 || bullets[i]->GetAnimRect()->GetPosition().x < -200)
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
