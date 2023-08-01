#include "stdafx.h"
#include "Scene_ForestFollies.h"

void SceneForestFollies::Init()
{
	player = make_shared<Player>(CENTER, Vector2(101, 159), 500.0f, 3, 100.0f);

	skyLayer = make_unique<TextureRect>(CENTER, Vector2(1898, 823) * 1.35, 0.0f, L"_Textures/Scene_ForestFollies/lv1-1_bg_sky_01.png");

	forestEnemySet = make_unique<ForestEnemySet>();
	forestObjectSet = make_unique<ForestObjectSet>();
}

void SceneForestFollies::Destroy()
{
}

void SceneForestFollies::Update()
{
	CheckGround();

	// playerBullts&enemies Collision
	for (auto& enemy : enemyList)
	{
		for (int i = 0; i < player->GetBullet()->GetBullets().size(); ++i)
		{
			if (player->GetBullet()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(enemy->GetAnimRect()->GET_COMP(Collider)))
			{
				enemy->SetHit(true);
				player->GetBullet()->GetBullets()[i]->SetActivation(false);
			}
		}

		for (int i = 0; i < player->GetSpecialAttack()->GetBullets().size(); ++i)
		{
			if (player->GetSpecialAttack()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(enemy->GetAnimRect()->GET_COMP(Collider)))
			{
				enemy->SetHit(true);
			}
		}
		
		if (player->GetSuperBeam()->GetAnimRect()->GET_COMP(Collider)->Intersect(enemy->GetAnimRect()->GET_COMP(Collider)))
			enemy->SetHit(true);
	}

	// Player&Enemies Collision
	for (auto& enemy : enemyList)
		enemy->Collision(player);
	// Player&Object Collision
	for (auto& object : objectList)
	{
		if (object->GetCollision())
			object->Collision(player);
	}

	// Delete Enemy
	for (int i = 0; i < enemyList.size(); ++i)
	{
		if (enemyList[i]->GetDelete())
			enemyList.erase(enemyList.begin() + i);
	}
	// Delete Object
	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetDelete())
			objectList.erase(objectList.begin() + i);
	}

	// Create Enemy
	if (forestEnemySet->GetSelectedIndex() == 0)
		enemyList.push_back(make_shared<FlowerGrunt>(CAMERA->GetPosition() + CENTER * 1.5, 1.0f, 300.0f, 1, 1, 1, Direction::R));

	// Create Object
	if (forestObjectSet->GetSelectedIndex() == 0)
		objectList.push_back(make_shared<Forest_Ground>(CAMERA->GetPosition() + CENTER, 1.0f, 0.0f, true));
	else if (forestObjectSet->GetSelectedIndex() == 1)
		objectList.push_back(make_shared<Forest_Wall>(CAMERA->GetPosition() + CENTER, 1.0f, 0.0f, true));

	// Enemies Update
	for (const auto& enemy : enemyList)
		enemy->Update();
	// ObjectList Update
	for (const auto& object : objectList)
		object->Update();

	player->Update();
	UI->Init(CAMERA->GetPosition(), player->GetHp(), player->GetPercentSuperMeterCard());
	UI->Update();

	if (!mod)
	{
		Vector2 temp = Vector2((player->GetAnimRect()->GetPosition().x - CENTER.x) - CAMERA->GetPosition().x, 0);
		CAMERA->SetPosition(Vector2(CAMERA->GetPosition().x + temp.x * 2 * DELTA, temp.y - 90));
	}

	CAMERA->Update();
	skyLayer->SetPosition(CAMERA->GetPosition() + CENTER + Vector2(0, 50));
	skyLayer->Update();
}

void SceneForestFollies::PreRender()
{
}

void SceneForestFollies::Render()
{
	CAMERA->Render();
	skyLayer->Render();

	for (const auto& object : objectList)
		object->Render();

	for (const auto& enemy : enemyList)
		enemy->Render();

	player->Render();

	UI->Render();
}

void SceneForestFollies::PostRender()
{
	player->GUI();

	forestEnemySet->GUI();
	forestObjectSet->GUI();

	IMGUI->ForestEnemyGUIS(enemyList, "ForestEmeny");
	IMGUI->ForestObjectGUIS(objectList, "ForestObject");

	static bool bOpen = true;
	if (ImGui::Begin("ForestFolliesMap", &bOpen))
	{
		if (ImGui::Button("Save", ImVec2(50, 30)))
			SaveForestFolliesMap();
		ImGui::SameLine();
		if (ImGui::Button("Load", ImVec2(50, 30)))
			LoadForestFolliesMap();

		ImGui::Checkbox("CreateMod", &mod);
		for (const auto& enemy : enemyList)
			enemy->SetMod(mod);
		player->SetMod(mod);
	}
	ImGui::End();
}

void SceneForestFollies::SaveForestFolliesMap(const wstring& path)
{
	if (path.empty())
	{
		function<void(wstring)> func = bind(&SceneForestFollies::SaveForestFolliesMap, this, placeholders::_1);
		Path::SaveFileDialog(L"", Path::ForestFilter, L"_Maps/", func, gHandle);
	}
	else
	{
		if (enemyList.empty()) return;

		ofstream out(path.c_str());

		if (out.is_open())
		{
			Vector2 tempPos = player->GetAnimRect()->GetPosition();
			out.write((char*)&tempPos, sizeof(tempPos));
			float tempSize = player->GetTotalSize();
			out.write((char*)&tempSize, sizeof(tempSize));

			int listSize = enemyList.size();
			out.write((char*)&listSize, sizeof(listSize));

			ForestEnemyState tempState;
			for (UINT i = 0; i < enemyList.size(); ++i)
			{
				tempState = enemyList[i]->GetState();
				out.write((char*)&tempState, sizeof(tempState));
			}
		}

		out.close();
	}
}

void SceneForestFollies::LoadForestFolliesMap(const wstring& path)
{
	if (path.empty())
	{
		function<void(wstring)> func = bind(&SceneForestFollies::LoadForestFolliesMap, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::ForestFilter, L"_Maps/", func, gHandle);
	}
	else
	{
		ifstream in(path.c_str());

		if (in.is_open())
		{
			Vector2 tempPos;
			in.read((char*)&tempPos, sizeof(tempPos));
			player->GetAnimRect()->SetPosition(tempPos);
			float tempSize;
			in.read((char*)&tempSize, sizeof(tempSize));
			player->SetTotalSize(tempSize);

			int listSize;
			in.read((char*)&listSize, sizeof(listSize));

			enemyList.clear();
			enemyList.resize(listSize);

			ForestEnemyState tempState;
			for (UINT i = 0; i < listSize; ++i)
			{
				in.read((char*)&tempState, sizeof(tempState));

				if (tempState.type == ForestEnemyType::FlowerGrunt)
					enemyList[i] = make_shared<FlowerGrunt>(tempState.position, tempState.totalSize, tempState.speed, tempState.maxHp, tempState.bRegen, tempState.regenTime, tempState.direction);
			}
		}

		in.close();
	}
}

// 각 플렛폼에서 검사할 예정
void SceneForestFollies::CheckGround()
{
	player->SetCheckCollider(0);
	player->SetPlatform(0);

	for (auto& enemy : enemyList)
	{
		for (auto& object : objectList)
		{
			if (object->GetState().type == ForestObjectType::Ground)
			{
				if (object->GetTextureRect()->GET_COMP(Collider)->Intersect(enemy->GetAnimRect()->GET_COMP(Collider)))
				{
					enemy->SetGroundPos(Vector2(object->GetTextureRect()->GetPosition().x, object->GetTextureRect()->GetPosition().y + object->GetTextureRect()->GetScale().y / 2));
				}
				else
					enemy->SetGroundPos(Vector2(-1000, -1000));
			}
			else if (object->GetState().type == ForestObjectType::Wall)
			{
				if (object->GetTextureRect()->GET_COMP(Collider)->Intersect(enemy->GetAnimRect()->GET_COMP(Collider)))
				{
					enemy->SetWall(true);
				}
			}
		}	
	}
}