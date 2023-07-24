#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(UINT totalBullet, float bulletSpeed, float speakerSpeed)
	: totalBullet(totalBullet), maxSpeed(bulletSpeed), speakerSpeed(speakerSpeed)
{
	// 초기화
	bulletIndex = 0;
	speed = 0;

	// 할당
	animRects.assign(this->totalBullet, make_shared<AnimationRect>());
	activation.assign(this->totalBullet, bool());
}

void Bullet::Update()
{
	// Move
	speed = maxSpeed;
	for (int i = 0; i < (int)totalBullet; ++i)
	{
		if (activation[i] == true)
			animRects[i]->Move(animRects[i]->GetRightVector() * maxSpeed);
	}
	for (auto& animRect : animRects)
		animRect->Update();
}

void Bullet::Render()
{
	for (int i = 0; i < (int)totalBullet; ++i)
	{
		if (activation[i] == true)
			animRects[i]->Render();
	}
}
