#include "stdafx.h"
#include "SquidBulletManager.h"

SquidBullet::SquidBullet()
{
	animRect = make_shared<AnimationRect>(Vector2(1000, -1000), Vector2(30, 30), 0.0f, L"_Textures/Pirate/pirate_squid_inkblob.png");

	// Up
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Idle", L"_Textures/Pirate/pirate_squid_inkblob.png", 36, false, true, 0.12f));

	// Death
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Death", L"_Textures/Pirate/pirate_squid_ink_death.png", 7, false, false, 0.12f));

	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::CIRCLE));

	animRect->SetAnimator(animRect->GET_COMP(Animator));
}

void SquidBullet::Collision(shared_ptr<Player> player)
{
	// player
	if (!bEnd && bActivation
		&& animRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
	{
		bActivation = false;
		INKSCREEN->Init(10.0f);
	}
}

void SquidBullet::Init(Vector2 position, float size, float speed, float jumpSpeed, float aclrt)
{
	this->totalSize = size;
	this->speed = speed;
	this->jumpSpeed = jumpSpeed;
	this->aclrt = aclrt;
	
	val = 0.0f;
	bEnd = false;
	bActivation = true;

	animRect->SetPosition(position);
}

void SquidBullet::Update()
{
	if (bActivation && !bEnd)
	{
		animRect->SetScale(Vector2(30, 30) * totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Idle");

		val += G * aclrt * DELTA;
		jumpSpeed -= val * DELTA;
		animRect->Move(Vector2(speed, jumpSpeed));
	}
	else if(bActivation)
	{
		animRect->SetScale(Vector2(175, 43) * totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Death");
		if (animRect->GET_COMP(Animator)->GetEnd())
		{
			bEnd = false;
			bActivation = false;
		}
	}

	if (animRect->GetPosition().y <= CAMERA->GetPosition().y)
		bActivation = false;

	animRect->Update();
}

void SquidBullet::Render()
{
	if (bActivation)
		animRect->Render();
}

// SquidBulletManager class
SquidBulletManager::SquidBulletManager()
{
	squidBulletList.resize(10);
	for (auto& squidBullet : squidBulletList)
		squidBullet = make_shared<SquidBullet>();

	random_device random;
	mt = mt19937(random());
}

SquidBulletManager::~SquidBulletManager() {}

void SquidBulletManager::Collision(shared_ptr<Player> player)
{
	for (auto& squidBullet : squidBulletList)
	{
		if (squidBullet->GetActivation())
			squidBullet->Collision(player);
	}
}

void SquidBulletManager::Create()
{
	squidBulletList.resize(squidBulletList.size() * 2);

	for (int i = squidBulletList.size() / 2; i < squidBulletList.size(); ++i)
		squidBulletList[i] = make_shared<SquidBullet>();
}

void SquidBulletManager::Init(Vector2 position, float size, int currentFrame)
{
	bActivation = true;
	this->totalSize = size;
	
	Vector2 AddPos = Vector2();
	switch (currentFrame)
	{
	case 0:
		AddPos = Vector2(-245, 160);
		break;
	case 1:
		AddPos = Vector2(-295, 110);
		break;
	case 2:
		AddPos = Vector2(-295, 95);
		break;
	case 3:
		AddPos = Vector2(-295, 85);
		break;
	case 4:
		AddPos = Vector2(-280, 135);
		break;
	case 5:
		AddPos = Vector2(-235, 170);
		break;
	case 6:
		AddPos = Vector2(-185, 185);
		break;
	case 7:
		AddPos = Vector2(-140, 165);
		break;
	case 8:
		AddPos = Vector2(-105, 150);
		break;
	case 9:
		AddPos = Vector2(-85, 130);
		break;
	case 10:
		AddPos = Vector2(-70, 115);
		break;
	case 11:
		AddPos = Vector2(-65, 95);
		break;
	case 12:
		AddPos = Vector2(-95, 135);
		break;
	case 13:
		AddPos = Vector2(-130, 157);
		break;
	case 14:
		AddPos = Vector2(-185, 175);
		break;
	}

	this->position = position + AddPos * totalSize;
}

void SquidBulletManager::Update()
{
	if (bActivation)
	{
		time += DELTA;
		if (time >= delayTime)
		{
			time = 0.0f;
			uniform_real_distribution<float> randomSpeed(MSpeed.x, MSpeed.y);
			uniform_real_distribution<float> randomJumpSpeed(MJumpSpeed.x, MJumpSpeed.y);
			if (!squidBulletList[currentIndex]->GetActivation())
				squidBulletList[currentIndex++]->Init(position, totalSize, randomSpeed(mt), randomJumpSpeed(mt), aclrt);
			else
				++currentIndex;

			if (currentIndex >= squidBulletList.size())
			{
				if (!squidBulletList[0]->GetActivation())
					currentIndex = 0;
				else
					Create();
			}
		}
	}

	for (auto& squidBullet : squidBulletList)
		squidBullet->Update();
}

void SquidBulletManager::Render()
{
	for (auto& squidBullet : squidBulletList)
		squidBullet->Render();
}

void SquidBulletManager::GUI()
{
	string objName = "SquidBullet";

	ImGui::Text(objName.c_str());
	ImGui::InputFloat("Scale", &totalSize, 0.1f, 10.0f, "%0.2f");
	ImGui::InputFloat("Acceleration", &aclrt, 0.1f, 100.0f, "%0.2f");

	ImGui::InputFloat("MinSpeed", (float*)&MSpeed.x, 1.0f, 100.0f);
	ImGui::InputFloat("MaxSpeed", (float*)&MSpeed.y, 1.0f, 100.0f);

	ImGui::InputFloat("MinJumpSpeed", (float*)&MJumpSpeed.x, 1.0f, 100.0f);
	ImGui::InputFloat("MaxJumpSpeed", (float*)&MJumpSpeed.y, 1.0f, 100.0f);

	ImGui::InputFloat("DelayTime", &delayTime, 0.1f, 3.0f);
}
