#include "stdafx.h"
#include "Scene_ForestFollies.h"

void SceneForestFollies::Init()
{
	player = make_shared<Player>(CENTER, Vector2(101, 159), 500.0f, 3, 100.0f);
	player->SetTotalSize(0.9f);

	skyLayer = make_unique<TextureRect>(CENTER, Vector2(1898, 823) * 1.35f, 0.0f, L"_Textures/Scene_ForestFollies/lv1-1_bg_sky_01.png");

	forestEnemySet = make_unique<ForestEnemySet>();
	forestObjectSet = make_unique<ForestObjectSet>();
	objectList.push_back(make_shared<Forest_Ground>(Vector2(640, -1.348), 6.0f, 0.0f, true));

	CAMERA->SetPosition(Vector2());
	CAMERA->SetEdges(false);

	IRISA->Start();

	SOUND->AddSound("Back", L"_Sounds/MUS_ForestFollies.wav", true);
	SOUND->Play("Back");
}

void SceneForestFollies::Destroy()
{
}

void SceneForestFollies::Update()
{
	if (!mod && IRISA->GetIsAnimEnd() && !bIntro)
	{
		bIntro = true;
		FIGHTTEXT->Init(FightTextType::RunNGun, true);
	}
	
	if (mod)
	{
		bIntro = false;
	}

	Collision();

	// Delete Enemy
	for (int i = 0; i < enemyList.size(); ++i)
	{
		if (enemyList[i]->GetDelete())
		{
			enemyList[i]->Destroy();
			enemyList.erase(enemyList.begin() + i);
		}
	}
	// Delete Object
	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetDelete())
			objectList.erase(objectList.begin() + i);
	}
	// Delete TextureRect
	for (int i = 0; i < trRectList.size(); ++i)
	{
		if (trRectList[i]->GetIsDelete())
			trRectList.erase(trRectList.begin() + i);
	}

	// Add Enemy
	if (forestEnemySet->GetSelectedIndex() == 0)
		enemyList.push_back(make_shared<FlowerGrunt>(CAMERA->GetPosition() + CENTER * 1.5, 0.72f, 300.0f, 1, true, 1.0f, Direction::L));
	else if (forestEnemySet->GetSelectedIndex() == 1)
		enemyList.push_back(make_shared<ForestBlob>(CAMERA->GetPosition() + CENTER * 1.5, 0.8f, 300.0f, 1, true, 5.0f, Direction::L));
	else if (forestEnemySet->GetSelectedIndex() == 2)
		enemyList.push_back(make_shared<Mushroom>(CAMERA->GetPosition() + CENTER * 1.5, 0.8f, 550.0f, 2, false, 0.0f, Direction::L));
	else if (forestEnemySet->GetSelectedIndex() == 3)
		enemyList.push_back(make_shared<Lobber>(CAMERA->GetPosition() + CENTER * 1.5, 0.72f, 2.0f, 5, false, 0.0f, Direction::L));
	else if (forestEnemySet->GetSelectedIndex() == 4)
		enemyList.push_back(make_shared<Chomper>(CAMERA->GetPosition() + CENTER * 1.5, 0.72f, 1200.0f, 0, true, 5.0f, Direction::R));
	else if (forestEnemySet->GetSelectedIndex() == 5)
		enemyList.push_back(make_shared<Spiker>(CAMERA->GetPosition() + CENTER * 1.5, 0.72f, 1.2f, 0, false, 150.0f, Direction::R));
	else if (forestEnemySet->GetSelectedIndex() == 6)
		enemyList.push_back(make_shared<Acorn>(CAMERA->GetPosition() + CENTER * 1.5, 0.8f, 650.0f, 3, true, 3.0f, Direction::L));
	else if (forestEnemySet->GetSelectedIndex() == 7)
		enemyList.push_back(make_shared<AcornMachine>(CAMERA->GetPosition() + CENTER * 1.5, 0.8f, 650.0f, 600, false, 1.0f, Direction::L));

	// Add Object
	if (forestObjectSet->GetSelectedIndex() == 0)
		objectList.push_back(make_shared<Forest_Ground>(CAMERA->GetPosition() + CENTER, 1.0f, 0.0f, true));
	else if (forestObjectSet->GetSelectedIndex() == 1)
		objectList.push_back(make_shared<Forest_Wall>(CAMERA->GetPosition() + CENTER, 1.0f, 0.0f, true));
	else if (forestObjectSet->GetSelectedIndex() == 2)
		objectList.push_back(make_shared<Forest_Hole>(CAMERA->GetPosition() + CENTER, 1.0f, 0.0f, true));
	else if (forestObjectSet->GetSelectedIndex() == 3)
		objectList.push_back(make_shared<FloatingPlatform>(ForestObjectType::FPlatform_a, CAMERA->GetPosition() + CENTER, 0.72f, 0.0f, true, 1, 100.0f));
	else if (forestObjectSet->GetSelectedIndex() == 4)
		objectList.push_back(make_shared<Forest_Exit>(CAMERA->GetPosition() + CENTER, 1.0f, 0.0f, true));

	// Add TextureRect
	if (INPUT->Down(VK_SPACE))
		if (!ImGui::IsAnyItemActive())
			trRectList.push_back(make_shared<TextureRect>(INPUT->GetMousePosition(), Vector2(300, 300), 0.0f));

	// NextScene
	if (nextScene && IRISA->GetIsAnimEnd())
	{
		deltaTime = 0.0f;
		nextScene = false;
		objectList.clear();
		vector<shared_ptr<IForestObjects>>().swap(objectList);

		enemyList.clear();
		vector<shared_ptr<IForestEnemy>>().swap(enemyList);
		SOUND->DeleteSound("Back");
		currentSceneIndex += 1;
	}

	// EnemyList Update
	for (const auto& enemy : enemyList)
		enemy->Update();
	// ObjectList Update
	for (const auto& object : objectList)
		object->Update();
	// TextureRectList Update
	for (const auto& trRect : trRectList)
		trRect->Update();

	// CAMERA
	if (!mod)
	{
		Vector2 temp = Vector2();
		if (!player->GetPlatform())
			temp = Vector2((player->GetAnimRect()->GetPosition().x - CENTER.x) - CAMERA->GetPosition().x, (player->GetGroundPos().y - 140) - CAMERA->GetPosition().y);
		else
			temp = Vector2((player->GetAnimRect()->GetPosition().x - CENTER.x) - CAMERA->GetPosition().x, 0);
		if (player->GetAnimRect()->GetPosition().y <= CAMERA->GetPosition().y + 140)
			temp.y = (player->GetAnimRect()->GetPosition().y - CENTER.y) - CAMERA->GetPosition().y;
		CAMERA->SetPosition(Vector2(CAMERA->GetPosition().x + temp.x * 2 * DELTA, CAMERA->GetPosition().y + temp.y * 2 * DELTA));
	}

	if (!bIntro)
		player->SetCheckCollider(true);

	player->Update();
	UI->Init(CAMERA->GetPosition(), player->GetHp(), player->GetPercentSuperMeterCard());
	UI->Update();

	CAMERA->Update();
	skyLayer->SetPosition(CAMERA->GetPosition() + CENTER + Vector2(0, 50));
	skyLayer->Update();

	FIGHTTEXT->Update();
}

void SceneForestFollies::PreRender()
{
}

void SceneForestFollies::Render()
{
	CAMERA->Render();
	skyLayer->Render();

	for (const auto& trRect : trRectList)
		trRect->Render();

	for (const auto& object : objectList)
		object->Render();

	for (const auto& enemy : enemyList)
		enemy->Render();

	player->Render();

	UI->Render();
	FIGHTTEXT->Render();
}

void SceneForestFollies::PostRender()
{
	player->GUI();

	forestEnemySet->GUI();
	forestObjectSet->GUI();

	IMGUI->ForestEnemyGUIS(enemyList, "ForestEmeny");
	IMGUI->ForestObjectGUIS(objectList, "ForestObject");
	IMGUI->TextureRectGUIS(trRectList, "TextureRects");

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
		for (const auto& object : objectList)
			object->SetMod(mod);
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
		if (enemyList.empty() && objectList.empty()) return;

		ofstream out(path.c_str());

		if (out.is_open())
		{
			// Player
			Vector2 tempPos = player->GetAnimRect()->GetPosition();
			out.write((char*)&tempPos, sizeof(tempPos));
			float tempSize = player->GetTotalSize();
			out.write((char*)&tempSize, sizeof(tempSize));

			// objectList
			int listSize = (int)objectList.size();
			out.write((char*)&listSize, sizeof(listSize));

			ForestObjectState tempObjectState;
			for (UINT i = 0; i < objectList.size(); ++i)
			{
				tempObjectState = objectList[i]->GetState();
				out.write((char*)&tempObjectState, sizeof(tempObjectState));
			}

			// enemyList
			listSize = (int)enemyList.size();
			out.write((char*)&listSize, sizeof(listSize));

			ForestEnemyState tempEnemyState;
			for (UINT i = 0; i < enemyList.size(); ++i)
			{
				tempEnemyState = enemyList[i]->GetState();
				out.write((char*)&tempEnemyState, sizeof(tempEnemyState));
			}

			string tempPath;
			Vector2 tempScale;
			if (!trRectList.empty())
			{
				listSize = (int)trRectList.size();
				out.write((char*)&listSize, sizeof(listSize));

				for (UINT i = 0; i < trRectList.size(); ++i)
				{
					tempPos = trRectList[i]->GetPosition();
					out.write((char*)&tempPos, sizeof(tempPos));

					tempScale = trRectList[i]->GetScale();
					out.write((char*)&tempScale, sizeof(tempScale));

					size_t tempLength = trRectList[i]->GetPath().length();
					out.write((char*)&tempLength, sizeof(tempLength));

					if (!trRectList[i]->GetPath().empty())
					{
						tempPath = String::ToString(trRectList[i]->GetPath());
						out.write(tempPath.c_str(), tempPath.size());
					}
				}
			}
			else
			{
				listSize = 0;
				out.write((char*)&listSize, sizeof(listSize));
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
			// Player
			Vector2 tempPos;
			in.read((char*)&tempPos, sizeof(tempPos));
			player->SetPosition(tempPos);
			float tempSize;
			in.read((char*)&tempSize, sizeof(tempSize));
			player->SetTotalSize(tempSize);

			// ObjectList
			int listSize;
			in.read((char*)&listSize, sizeof(listSize));

			objectList.clear();
			objectList.resize(listSize);

			ForestObjectState tempObjectState;
			for (UINT i = 0; i < listSize; ++i)
			{
				in.read((char*)&tempObjectState, sizeof(tempObjectState));

				if (tempObjectState.type == ForestObjectType::Ground)
					objectList[i] = make_shared<Forest_Ground>(tempObjectState.position, tempObjectState.totalSize, tempObjectState.rotation, tempObjectState.bCollision);
				else if (tempObjectState.type == ForestObjectType::Wall)
					objectList[i] = make_shared<Forest_Wall>(tempObjectState.position, tempObjectState.totalSize, tempObjectState.rotation, tempObjectState.bCollision);
				else if (tempObjectState.type == ForestObjectType::Hole)
					objectList[i] = make_shared<Forest_Hole>(tempObjectState.position, tempObjectState.totalSize, tempObjectState.rotation, tempObjectState.bCollision);
				else if (tempObjectState.type >= ForestObjectType::FPlatform_a && tempObjectState.type <= ForestObjectType::FPlatform_c)
					objectList[i] = make_shared<FloatingPlatform>(tempObjectState.type, tempObjectState.position, tempObjectState.totalSize, tempObjectState.rotation, tempObjectState.bCollision, tempObjectState.direction, tempObjectState.moveScale);
				else if (tempObjectState.type == ForestObjectType::Exit)
					objectList[i] = make_shared<Forest_Exit>(tempObjectState.position, tempObjectState.totalSize, tempObjectState.rotation, tempObjectState.bCollision);
			}

			// EnemyList
			listSize;
			in.read((char*)&listSize, sizeof(listSize));

			enemyList.clear();
			enemyList.resize(listSize);

			ForestEnemyState tempEnemyState;
			for (UINT i = 0; i < listSize; ++i)
			{
				in.read((char*)&tempEnemyState, sizeof(tempEnemyState));

				if (tempEnemyState.type == ForestEnemyType::FlowerGrunt)
					enemyList[i] = make_shared<FlowerGrunt>(tempEnemyState.position, tempEnemyState.totalSize, tempEnemyState.speed, tempEnemyState.maxHp, tempEnemyState.bRegen, tempEnemyState.regenTime, tempEnemyState.direction);
				else if (tempEnemyState.type == ForestEnemyType::Blob)
					enemyList[i] = make_shared<ForestBlob>(tempEnemyState.position, tempEnemyState.totalSize, tempEnemyState.speed, tempEnemyState.maxHp, tempEnemyState.bRegen, tempEnemyState.regenTime, tempEnemyState.direction);
				else if (tempEnemyState.type == ForestEnemyType::Mushroom)
					enemyList[i] = make_shared<Mushroom>(tempEnemyState.position, tempEnemyState.totalSize, tempEnemyState.speed, tempEnemyState.maxHp, tempEnemyState.bRegen, tempEnemyState.regenTime, tempEnemyState.direction);
				else if (tempEnemyState.type == ForestEnemyType::Lobber)
					enemyList[i] = make_shared<Lobber>(tempEnemyState.position, tempEnemyState.totalSize, tempEnemyState.speed, tempEnemyState.maxHp, tempEnemyState.bRegen, tempEnemyState.regenTime, tempEnemyState.direction);
				else if (tempEnemyState.type == ForestEnemyType::Chomper)
					enemyList[i] = make_shared<Chomper>(tempEnemyState.position, tempEnemyState.totalSize, tempEnemyState.speed, tempEnemyState.maxHp, tempEnemyState.bRegen, tempEnemyState.regenTime, tempEnemyState.direction);
				else if (tempEnemyState.type == ForestEnemyType::Spiker)
					enemyList[i] = make_shared<Spiker>(tempEnemyState.position, tempEnemyState.totalSize, tempEnemyState.speed, tempEnemyState.maxHp, tempEnemyState.bRegen, tempEnemyState.regenTime, tempEnemyState.direction);
				else if (tempEnemyState.type == ForestEnemyType::Acorn)
					enemyList[i] = make_shared<Acorn>(tempEnemyState.position, tempEnemyState.totalSize, tempEnemyState.speed, tempEnemyState.maxHp, tempEnemyState.bRegen, tempEnemyState.regenTime, tempEnemyState.direction);
				else if (tempEnemyState.type == ForestEnemyType::AcornMachine)
					enemyList[i] = make_shared<AcornMachine>(tempEnemyState.position, tempEnemyState.totalSize, tempEnemyState.speed, tempEnemyState.maxHp, tempEnemyState.bRegen, tempEnemyState.regenTime, tempEnemyState.direction);
			}

			in.read((char*)&listSize, sizeof(listSize));

			trRectList.clear();
			trRectList.resize(listSize);

			if (listSize)
			{
				wstring tempPath;
				Vector2 tempScale;
				for (UINT i = 0; i < listSize; ++i)
				{
					in.read((char*)&tempPos, sizeof(tempPos));
					in.read((char*)&tempScale, sizeof(tempScale));

					size_t tempLength = 0;
					in.read((char*)&tempLength, sizeof(tempLength));
					if (tempLength)
					{
						string str = "";
						str.resize(tempLength);
						in.read(&str[0], tempLength);
						tempPath = String::ToWString(str);
					}

					trRectList[i] = make_shared<TextureRect>(tempPos, tempScale, 0.0f, tempPath);
				}
			}
		}

		in.close();
	}
}

void SceneForestFollies::Collision()
{
	for (auto& enemy : enemyList)
		enemy->SetGroundPos(Vector2(-1000, -1000));
	for (auto& object : objectList)
	{
		for (auto& enemy : enemyList)
		{
			if (object->GetState().type == ForestObjectType::Ground)
			{
				if (object->GetTextureRect()->GET_COMP(Collider)->Intersect(enemy->GetAnimRect()->GET_COMP(Collider)))
					enemy->SetGroundPos(Vector2(object->GetTextureRect()->GetPosition().x, object->GetTextureRect()->GetPosition().y + object->GetTextureRect()->GetScale().y / 2));

				if (enemy->GetState().type == ForestEnemyType::Lobber)
				{
					for (int i = 0; i < enemy->GetBullet()->GetBullets().size(); ++i)
					{
						if (object->GetTextureRect()->GET_COMP(Collider)->Intersect(enemy->GetBullet()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)))
						{
							enemy->GetBullet()->GetBullets()[i]->SetGround(true);
						}
					}
				}
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

	// playerBullts&enemies Collision
	for (auto& enemy : enemyList)
	{
		for (int i = 0; i < player->GetBullet()->GetBullets().size(); ++i)
		{
			if (player->GetBullet()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(enemy->GetAnimRect()->GET_COMP(Collider)) && enemy->GetHp() > 0)
			{
				if (!player->GetBullet()->GetBullets()[i]->GetHit())
				{
					enemy->SetHit(true);
					player->GetBullet()->GetBullets()[i]->SetIsHit(true);
					player->SetSuperMeterCard(player->GetSuperMeterCard() + 1);
				}
			}
		}

		for (int i = 0; i < player->GetSpecialAttack()->GetBullets().size(); ++i)
		{
			if (player->GetSpecialAttack()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(enemy->GetAnimRect()->GET_COMP(Collider)) && enemy->GetHp() > 0)
			{
				enemy->SetHit(true);
			}
		}

		if (player->GetSuperBeam()->GetAnimRect()->GET_COMP(Collider)->Intersect(enemy->GetAnimRect()->GET_COMP(Collider)) && enemy->GetHp() > 0)
			enemy->SetHit(true);
	}

	// Player&Enemies Collision
	for (auto& enemy : enemyList)
		enemy->Collision(player);
	// Player&Object Collision
	player->SetCheckCollider(false);
	player->SetPlatform(false);
	for (auto& object : objectList)
	{
		if (object->GetCollision())
		{
			if (object->Collision(player))
				player->SetCheckCollider(true);
			else if (object->GetState().type == ForestObjectType::Exit)
			{
				if (dynamic_pointer_cast<Forest_Exit>(object)->GetNextScene() && IRISA->GetIsAnimEnd())
				{
					deltaTime += DELTA;
					if (!nextScene && deltaTime >= 2.0f)
					{
						nextScene = true;
						IRISA->End();
					}
				}
			}
		}
	}
}
