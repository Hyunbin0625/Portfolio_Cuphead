#include "stdafx.h"
#include "CroaksAttackManager.h"

CroaksAttackManager::CroaksAttackManager()
{
	pSnakeList.resize(4);
	for (auto& pSnake : pSnakeList)
		pSnake = make_shared<CroaksPSnake>();
	pTigerList.resize(4);
	for (auto& pTiger : pTigerList)
		pTiger = make_shared<CroaksPTiger>();
	pBisonList.resize(4);
	for (auto& pBison : pBisonList)
		pBison = make_shared<CroaksPBison>();

	regenTime = 1.0f;
	random_device random;
	mt = mt19937(random());

	SOUND->AddSound("FirFlyDeath", L"_Sounds/sfx_frogs_tall_firefly_death_01.wav", false, true);

	SOUND->AddSound("BBurst", L"_Sounds/sfx_frogs_flame_platform_fire_burst_01.wav", false, true);
	SOUND->AddSound("BBall", L"_Sounds/sfx_frogs_ball_platform_ball_launch_01.wav", false, true);
}

CroaksAttackManager::~CroaksAttackManager() {}

void CroaksAttackManager::CreateBullet(int addSize)
{
	totalIndex += addSize;
	bullets.resize(totalIndex);

	for (int i = totalIndex - addSize; i < totalIndex; ++i)
		bullets[i] = make_shared<CroaksFirefly>(bulletSpeed);
}

void CroaksAttackManager::InitBullet(UINT maxBullet, float bulletSpeed)
{
	this->maxBullet = maxBullet;
	this->bulletSpeed = bulletSpeed;

	totalIndex = maxBullet;
	createPos = Vector2(-170, 165);

	bullets.resize(totalIndex);
	for (auto& bullet : bullets)
		bullet = make_shared<CroaksFirefly>(bulletSpeed);
}

void CroaksAttackManager::InitSize()
{
	// 檬扁拳
	count = 0;
	currentIndex = 0;
	totalSize = 1.0f;

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

	bullets[currentIndex]->Init(position + createPos * totalSize, Vector2(startPosX(mt), startPosY(mt)));
	++count;
}

void CroaksAttackManager::InitPlatform(Vector2 position, float speed, SlotType type)
{
	this->position = position;
	bulletSpeed = speed;
	this->type = type;
	if (type == SlotType::Snake)
	{
		for (auto& pSnake : pSnakeList)
			pSnake->SetSpeed(speed);
	}
	else if (type == SlotType::Bison)
	{
		for (auto& pBison : pBisonList)
			pBison->SetSpeed(speed - 100.0f);
	}
	else if (type == SlotType::tiger)
	{
		for (auto& pTiger : pTigerList)
			pTiger->SetSpeed(speed - 100.0f);
	}

	count = 0;
	currentIndex = 0;
	time = 0.0f;
	bPlatform = true;
	bEnd = false;
}

void CroaksAttackManager::CreatePlatform()
{
	switch (type)
	{
	case SlotType::Snake:
		pSnakeList.resize(pSnakeList.size() * 2);
		for (int i = pSnakeList.size() / 2; i < pSnakeList.size(); ++i)
			pSnakeList[i] = make_shared<CroaksPSnake>();
		break;
	case SlotType::Bison:
		pBisonList.resize(pBisonList.size() * 2);
		for (int i = pBisonList.size() / 2; i < pBisonList.size(); ++i)
			pBisonList[i] = make_shared<CroaksPBison>();
		break;
	case SlotType::tiger:
		pTigerList.resize(pTigerList.size() * 2);
		for (int i = pTigerList.size() / 2; i < pTigerList.size(); ++i)
			pTigerList[i] = make_shared<CroaksPTiger>();
		break;
	}
}

void CroaksAttackManager::Update()
{
	if (bPlatform)
	{
		time += DELTA;
		switch (type)
		{
		case SlotType::Snake:
			if (time >= regenTime - count / 45.0f)
			{
				if (!pSnakeList[currentIndex]->GetActivation())
				{
					++count;
					pSnakeList[currentIndex++]->Init(position, groundY);
					time = 0.0f;
				}
				// pSnakeList 包府
				if (currentIndex >= pSnakeList.size())
				{
					if (pSnakeList.front()->GetActivation())
						CreatePlatform();
					else
						currentIndex = 0;
				}
			}
			break;
		case SlotType::Bison:
			if (time >= regenTime)
			{
				if (!pBisonList[currentIndex]->GetActivation())
				{
					++count;
					pBisonList[currentIndex++]->Init(position, groundY + addGroundY);
					time = 0.0f;
				}
				// pBisonList 包府
				if (currentIndex >= pBisonList.size())
				{
					if (pBisonList.front()->GetActivation())
						CreatePlatform();
					else
						currentIndex = 0;
				}
			}
			break;
		case SlotType::tiger:
			if (time >= regenTime)
			{
				if (!pTigerList[currentIndex]->GetActivation())
				{
					++count;
					pTigerList[currentIndex++]->Init(position, groundY);
					time = 0.0f;
				}
				// pTigerList 包府
				if (currentIndex >= pTigerList.size())
				{
					if (pTigerList.front()->GetActivation())
						CreatePlatform();
					else
						currentIndex = 0;
				}
			}
			break;
		}
		// max
		if (count >= 23)
		{
			bEnd = true;
			bPlatform = false;
		}
	}

	for (auto& bullet : bullets)
	{
		bullet->SetTotalSize(totalSize);
		bullet->SetSpeed(bulletSpeed);

		if (bullet->GetActivation())
			bullet->Update();
	}	
	
	for (auto& pSnake : pSnakeList)
	{
		pSnake->SetTotalSize(totalSize);
		pSnake->SetSpeed(bulletSpeed);

		if (pSnake->GetActivation())
			pSnake->Update();
	}

	for (auto& pTiger : pTigerList)
	{
		pTiger->SetTotalSize(totalSize);
		pTiger->SetSpeed(bulletSpeed);

		if (pTiger->GetActivation())
			pTiger->Update();
	}

	for (auto& pBison : pBisonList)
	{
		pBison->SetTotalSize(totalSize);
		pBison->SetSpeed(bulletSpeed);

		if (pBison->GetActivation())
			pBison->Update();
	}
}

void CroaksAttackManager::Render()
{
	for (auto& bullet : bullets)
	{
		if (bullet->GetActivation())
			bullet->Render();
	}
	for (auto& pSnake : pSnakeList)
	{
		if (pSnake->GetActivation())
			pSnake->Render();
	}
	for (auto& pTiger : pTigerList)
	{
		if (pTiger->GetActivation())
			pTiger->Render();
	}
	for (auto& pBison : pBisonList)
	{
		if (pBison->GetActivation())
			pBison->Render();
	}
}

void CroaksAttackManager::GUI()
{
	bool temp = true;
	if (ImGui::Begin("CroaksAttackManager"), &temp)
	{
		FireFlyGUI();
		PSnakeGUI();
		PTigerGUI();
		PBisonGUI();
	}
	ImGui::End();
}

void CroaksAttackManager::FireFlyGUI()
{
	string objName = "FireFly";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		for (auto& bullet : bullets)
			bullet->GetAnimRect()->SetOutline(true);

		ImGui::Text(objName.c_str());

		ImGui::SliderFloat2("CreatePos(+pos)", (float*)&createPos, CAMERA->GetPosition().x - createPos.x, CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH - createPos.y);
		int tempHp = bullets[0]->GetHp();
		if (ImGui::InputInt("Hp", &tempHp))
		{
			for (auto& bullet : bullets)
				bullet->SetHp(tempHp);
		}
		float tempSpeed = bullets[0]->GetSpeed();
		if (ImGui::SliderFloat("Speed", &tempSpeed, 500.0f, 1000.0f, "%.2f"))
		{
			for (auto& bullet : bullets)
				bullet->SetSpeed(tempSpeed);
		}

		ImGui::EndMenu();
	}
	else
	{
		for (auto& bullet : bullets)
			bullet->GetAnimRect()->SetOutline(false);
	}
}

void CroaksAttackManager::PSnakeGUI()
{
		string objName = "PlatformSnake";

		if (ImGui::BeginMenu(objName.c_str()))
		{
			for (auto& pSnake : pSnakeList)
				pSnake->GetAnimRect()->SetOutline(true);

			ImGui::Text(objName.c_str());

			ImGui::InputFloat("RegenTime", &regenTime);
			float tempSpeed = pSnakeList[0]->GetSpeed();
			if (ImGui::SliderFloat("Speed", &tempSpeed, 500.0f, 1000.0f, "%.2f"))
			{
				for (auto& pSnake : pSnakeList)
					pSnake->SetSpeed(tempSpeed);
			}

			ImGui::EndMenu();
		}
		else
		{
			for (auto& pSnake : pSnakeList)
				pSnake->GetAnimRect()->SetOutline(false);
		}
}

void CroaksAttackManager::PTigerGUI()
{
	string objName = "PlatformTiger";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		for (auto& pTiger : pTigerList)
			pTiger->GetAnimRect()->SetOutline(true);

		ImGui::Text(objName.c_str());

		ImGui::InputFloat("RegenTime", &regenTime);
		float tempSpeed = pTigerList[0]->GetSpeed();
		if (ImGui::SliderFloat("Speed", &tempSpeed, 500.0f, 1000.0f, "%.2f"))
		{
			for (auto& pTiger : pTigerList)
				pTiger->SetSpeed(tempSpeed);
		}
		float tempJumpSpeed = pTigerList[0]->GetJumpSpeed();
		if (ImGui::SliderFloat("JumpSpeed", &tempJumpSpeed, 500.0f, 2000.0f, "%.2f"))
		{
			for (auto& pTiger : pTigerList)
				pTiger->SetJumpSpeed(tempJumpSpeed);
		}
		ImGui::EndMenu();
	}
	else
	{
		for (auto& pTiger : pTigerList)
			pTiger->GetAnimRect()->SetOutline(false);
	}
}

void CroaksAttackManager::PBisonGUI()
{
	string objName = "PlatformBison";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		for (auto& pBison : pBisonList)
			pBison->GetAnimRect()->SetOutline(true);

		ImGui::Text(objName.c_str());

		ImGui::InputFloat("RegenTime", &regenTime);
		float tempSpeed = pBisonList[0]->GetSpeed();
		if (ImGui::SliderFloat("Speed", &tempSpeed, 500.0f, 1000.0f, "%.2f"))
		{
			for (auto& pBison : pBisonList)
				pBison->SetSpeed(tempSpeed);
		}
		float tempFlameTime = pBisonList[0]->GetFlameTime();
		if (ImGui::SliderFloat("FlameTime", &tempFlameTime, 0.2f, 30.0f, "%.2f"))
		{
			for (auto& pBison : pBisonList)
				pBison->SetFlameTime(tempFlameTime);
		}
		ImGui::SliderFloat("AddGroundPosY", &addGroundY, 0, CAMERA->GetPosition().y + WIN_DEFAULT_WIDTH - groundY, "%.2f");

		ImGui::EndMenu();
	}
	else
	{
		for (auto& pBison : pBisonList)
			pBison->GetAnimRect()->SetOutline(false);
	}
}