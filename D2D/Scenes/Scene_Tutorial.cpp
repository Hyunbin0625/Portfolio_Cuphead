#include "stdafx.h"
#include "Scene_Tutorial.h"

void SceneTutorial::Init()
{
	player = make_shared<Player>(CENTER, Vector2(101, 159), 500.0f, 3, 100.0f);

	backLayer = make_unique<TextureRect>(CENTER, Vector2(WIN_DEFAULT_WIDTH, WIN_DEFAULT_HEIGHT), 0.0f, L"_Textures/Scene_Tutorial/tutorial_room_back_layer.png");
	frontLayer = make_unique<TextureRect>(CENTER, Vector2(WIN_DEFAULT_WIDTH, WIN_DEFAULT_HEIGHT), 0.0f, L"_Textures/Scene_Tutorial/tutorial_room_front_layer.png");

	ground = make_unique<ColorRect>(Vector2(5000, 300), Vector2(10000, 50), 0.0f, BLACK);
	ground->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));

	tutoSet = make_unique<TutoSet>();
}

void SceneTutorial::Destroy()
{
}

void SceneTutorial::Update()
{
	CheckGround();

	for (auto& object : objectList)
	{
		if (object->GetCollision())
			object->Collision(player);
	}

	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetDelete())
			objectList.erase(objectList.begin() + i);
	}

	if (tutoSet->GetSelectedIndex() == 0)
		objectList.push_back(make_shared<Tuto_Cube>(CAMERA->GetPosition() + CENTER, 1.0f, 0.0f, 0));

	for (const auto& object : objectList)
		object->Update();

	ground->Update();
	player->Update();
	UI->Init(CAMERA->GetPosition(), player->GetHp(), player->GetPercentSuperMeterCard());
	UI->Update();

	Vector2 temp = Vector2((player->GetAnimRect()->GetPosition().x - CENTER.x) - CAMERA->GetPosition().x, 0);
	CAMERA->SetPosition(Vector2(CAMERA->GetPosition().x + temp.x * 2 * DELTA, temp.y + 210));

	CAMERA->Update();
	backLayer->SetPosition(CAMERA->GetPosition() + CENTER);
	frontLayer->SetPosition(CAMERA->GetPosition() + CENTER);
	backLayer->Update();
	frontLayer->Update();
}

void SceneTutorial::PreRender()
{
}

void SceneTutorial::Render()
{
	CAMERA->Render();
	backLayer->Render();
	{
		ground->Render();

		for (const auto& object : objectList)
			object->Render();

		player->Render();
	}
	frontLayer->Render();
	UI->Render();
}

void SceneTutorial::PostRender()
{
	player->GUI();

	tutoSet->GUI();
	
	IMGUI->TutoObjectGUIS(objectList, "TutoObjects");

	static bool bOpen = true;
	if (ImGui::Begin("TutorialMap", &bOpen))
	{
		if (ImGui::Button("Save", ImVec2(50, 30)))
			SaveTutorialMap();
		ImGui::SameLine();
		if (ImGui::Button("Load", ImVec2(50, 30)))
			LoadTutorialMap();
	}
	ImGui::End();
}

void SceneTutorial::SaveTutorialMap(const wstring& path)
{
	if (path.empty())
	{
		function<void(wstring)> func = bind(&SceneTutorial::SaveTutorialMap, this, placeholders::_1);
		Path::SaveFileDialog(L"", Path::TutorialFilter, L"_Maps/", func, gHandle);
	}
	else
	{
		if (objectList.empty()) return;

		ofstream out(path.c_str());

		if (out.is_open())
		{
			Vector2 tempPos = player->GetAnimRect()->GetPosition();
			out.write((char*)&tempPos, sizeof(tempPos));
			float tempSize = player->GetTotalSize();
			out.write((char*)&tempSize, sizeof(tempSize));

			int listSize = (int)objectList.size();
			out.write((char*)&listSize, sizeof(listSize));

			TutoState tempState;
			for (UINT i = 0; i < objectList.size(); ++i)
			{
				tempState = objectList[i]->GetState();
				out.write((char*)&tempState, sizeof(tempState));
			}
		}

		out.close();
	}
}

void SceneTutorial::LoadTutorialMap(const wstring& path)
{
	if (path.empty())
	{
		function<void(wstring)> func = bind(&SceneTutorial::LoadTutorialMap, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::TutorialFilter, L"_Maps/", func, gHandle);
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

			objectList.clear();
			objectList.resize(listSize);

			TutoState tempState;
			for (UINT i = 0; i < listSize; ++i)
			{
				in.read((char*)&tempState, sizeof(tempState));

				if (tempState.type == TutoType::Cube)
					objectList[i] = make_shared<Tuto_Cube>(tempState.position, tempState.totalSize, tempState.rotation, tempState.bCollision);
			}
		}

		in.close();
	}
}

// 각 플렛폼에서 검사할 예정
void SceneTutorial::CheckGround()
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
}