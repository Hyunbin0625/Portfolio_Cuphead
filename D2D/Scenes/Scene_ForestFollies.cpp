#include "stdafx.h"
#include "Scene_ForestFollies.h"

void SceneForestFollies::Init()
{
	player = make_shared<Player>(CENTER, Vector2(101, 159), 500.0f, 3, 100.0f);

	skyLayer = make_unique<TextureRect>(CENTER, Vector2(1898, 823) * 1.35, 0.0f, L"_Textures/Scene_ForestFollies/lv1-1_bg_sky_01.png");

	ground = make_unique<ColorRect>(Vector2(5000, 0), Vector2(10000, 50), 0.0f, BLACK);
	wall = make_unique<ColorRect>(Vector2(100, 150), Vector2(50, 300), 0.0f, BLACK);
	wall1 = make_unique<ColorRect>(Vector2(500, 150), Vector2(50, 300), 0.0f, BLACK);

	// 임시
	ground->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
	wall->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
	wall1->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));

	forestEnemySet = make_unique<ForestEnemySet>();
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
				cout << "true\n";
				enemy->SetHit(true);
				player->GetBullet()->SetActivation(i, false);
			}
		}
	}

	// Player&Enemies Collision
	for (auto& enemy : enemyList)
		enemy->Collision(player);

	// Delete Enemy
	for (int i = 0; i < enemyList.size(); ++i)
	{
		if (enemyList[i]->GetDelete())
			enemyList.erase(enemyList.begin() + i);
	}

	// Create Enemy
	if (forestEnemySet->GetSelectedIndex() == 0)
		enemyList.push_back(make_shared<FlowerGrunt>(CAMERA->GetPosition() + CENTER, 1.0f, 300.0f, 1, 1, 1, Direction::R));

	// Enemies Update
	for (const auto& enemy : enemyList)
		enemy->Update();

	ground->Update();
	wall->Update();
	wall1->Update();

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

	ground->Render();
	wall->Render();
	wall1->Render();

	for (const auto& enemy : enemyList)
		enemy->Render();

	player->Render();

	UI->Render();
}

void SceneForestFollies::PostRender()
{
	player->GUI();

	forestEnemySet->GUI();

	IMGUI->ForestEnemyGUIS(enemyList, "ForestEmeny");

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
	if (ground->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= PlayerState::Special_Attack_R && player->GetState() <= PlayerState::Super_Beam_L))
	{
		player->SetGroundPos(Vector2(ground->GetPosition().x, ground->GetPosition().y + ground->GetScale().y / 2));
		player->SetCheckCollider(1);
		if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < ground->GetPosition().y + ground->GetScale().y / 2 - 1)
			player->GetAnimRect()->Move(Vector2(0, 100));
	}

	for (auto& enemy : enemyList)
	{
		if (ground->GET_COMP(Collider)->Intersect(enemy->GetAnimRect()->GET_COMP(Collider)))
		{
			enemy->SetGroundPos(Vector2(ground->GetPosition().x, ground->GetPosition().y + ground->GetScale().y / 2));
		}
		else
			enemy->SetGroundPos(Vector2(-1000, -1000));
	}

	for (auto& enemy : enemyList)
	{
		if (wall->GET_COMP(Collider)->Intersect(enemy->GetAnimRect()->GET_COMP(Collider)))
		{
			enemy->SetWall(true);
		}
	}
}