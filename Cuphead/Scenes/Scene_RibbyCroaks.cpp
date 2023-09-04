#include "stdafx.h"
#include "Scene_RibbyCroaks.h"

void SceneRibbyCroaks::Init()
{
	// √ ±‚»≠
	bIntro = false;

	player = make_shared<Player>(Vector2(284, 116.602f), Vector2(101, 159), 500.0f, 3, 100.0f);
	player->SetTotalSize(1.1f);

	ribbyCroaks = make_shared<RibbyCroaks>(RibbyCroaksInfo{ Vector2(1028, 191), 1.2 }, RibbyCroaksInfo{ Vector2(1080, 322), 1.0 }, 1000, 5.0f);

	// backGround
	tempBackGround = make_unique<TextureRect>(CENTER, Vector2(1280, 720) * 1.4, 0.0f, L"_Textures/RibbyCroaks/FrogsBackGround.png");

	forestObjectSet = make_unique<ForestObjectSet>();
	objectList.push_back(make_shared<Forest_Ground>(Vector2(640, -1.348), 6.0f, 0.0f, true));

	CAMERA->SetPosition(Vector2());

	IRISA->Start();

	SOUND->AddSound("Back", L"_Sounds/MUS_Frogs.wav", true);
	SOUND->Play("Back");
}

void SceneRibbyCroaks::Destroy()
{
}

void SceneRibbyCroaks::Update()
{
	// Intro
	if (!mod && IRISA->GetIsAnimEnd() && !bIntro)
	{
		bIntro = true;
		player->SetIntro(true);
		ribbyCroaks->SetCIntro(true);
		FIGHTTEXT->Init(FightTextType::Boss_A, true);
	}

	if (mod)
	{
		bIntro = false;
	}

	player->SetCheckCollider(false);
	player->SetPlatform(false);

	// Player&Enemies Collision
	ribbyCroaks->Collision(player);

	// EnemieBullet&Object Collision
	float groundY = 0.0f;
	for (auto& object : objectList)
	{
		if (object->GetState().type == ForestObjectType::Ground)
			groundY = object->GetTextureRect()->GetPosition().y + object->GetTextureRect()->GetScale().y * 0.5f;
	}
	CATTACKMANAGER->SetGroundY(groundY - 0.152f);

	// Player&Object Collision
	for (auto& object : objectList)
	{
		if (object->GetCollision())
		{
			if (object->Collision(player))
				player->SetCheckCollider(true);
		}
	}

	// Delete Object
	for (int i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetDelete())
			objectList.erase(objectList.begin() + i);
	}

	// Create Object
	if (forestObjectSet->GetSelectedIndex() == 0)
		objectList.push_back(make_shared<Forest_Ground>(CAMERA->GetPosition() + CENTER, 1.0f, 0.0f, true));
	else if (forestObjectSet->GetSelectedIndex() == 1)
		objectList.push_back(make_shared<Forest_Wall>(CAMERA->GetPosition() + CENTER, 1.0f, 0.0f, true));
	else if (forestObjectSet->GetSelectedIndex() == 2)
		objectList.push_back(make_shared<FloatingPlatform>(ForestObjectType::FPlatform_a, CAMERA->GetPosition() + CENTER, 0.72f, 0.0f, true, 1, 100.0f));

	// NextScene
	if (ribbyCroaks->GetHp() <= 0)
	{
		deltaTime += DELTA;

		if (deltaTime <= 1.0f)
			FIGHTTEXT->Init(FightTextType::Boss_B, false, true);

		if ((int)deltaTime == 5)
			IRISA->End();

		if (deltaTime >= 5 && IRISA->GetIsAnimEnd())
		{
			deltaTime = 0.0f;
			ribbyCroaks->Destroy();
			SOUND->DeleteSound("Back");
			currentSceneIndex += 1;
		}
	}

	tempBackGround->Update();

	// ObjectList Update
	for (const auto& object : objectList)
		object->Update();

	ribbyCroaks->Update();

	// CAMERA
	CAMERA->SetEdges(Vector2(tempBackGround->GetPosition().x - tempBackGround->GetScale().x * 0.5f + 210, tempBackGround->GetPosition().y - tempBackGround->GetScale().y * 0.5f),
		Vector2(tempBackGround->GetPosition().x + tempBackGround->GetScale().x * 0.5f - 243, tempBackGround->GetPosition().y + tempBackGround->GetScale().y * 0.5f));
	Vector2 temp = Vector2((player->GetAnimRect()->GetPosition().x - CENTER.x) - CAMERA->GetPosition().x, 0);
	CAMERA->SetPosition(Vector2(CAMERA->GetPosition().x + temp.x * 2 * DELTA, tempBackGround->GetPosition().y - (CENTER_Y + 40)));

	if (!bIntro)
		player->SetCheckCollider(true);

	player->Update();
	UI->Init(CAMERA->GetPosition(), player->GetHp(), player->GetPercentSuperMeterCard());
	UI->Update();

	CAMERA->Update();
	FIGHTTEXT->Update();
}

void SceneRibbyCroaks::PreRender()
{
}

void SceneRibbyCroaks::Render()
{
	CAMERA->Render();
	tempBackGround->Render();

	for (const auto& object : objectList)
		object->Render();

	ribbyCroaks->Render();

	player->Render();

	UI->Render();
	FIGHTTEXT->Render();
}

void SceneRibbyCroaks::PostRender()
{
	player->GUI();
	ribbyCroaks->GUI();
	forestObjectSet->GUI();
	IMGUI->ForestObjectGUIS(objectList, "Object");

	static bool bOpen = true;
	if (ImGui::Begin("RibbyCroaksScene", &bOpen))
	{
		if (ImGui::Button("Save", ImVec2(50, 30)))
			SaveRibbyCroaks();
		ImGui::SameLine();
		if (ImGui::Button("Load", ImVec2(50, 30)))
			LoadRibbyCroaks();

		ImGui::Checkbox("CreateMod", &mod);
		for (const auto& object : objectList)
			object->SetMod(mod);
		player->SetMod(mod);
		ribbyCroaks->SetMod(mod);
	}
	ImGui::End();
}

void SceneRibbyCroaks::SaveRibbyCroaks(const wstring& path)
{
	if (path.empty())
	{
		function<void(wstring)> func = bind(&SceneRibbyCroaks::SaveRibbyCroaks, this, placeholders::_1);
		Path::SaveFileDialog(L"", Path::RibbyCroaksFilter, L"_Maps/", func, gHandle);
	}
	else
	{
		ofstream out(path.c_str());

		if (out.is_open())
		{
			// Player
			Vector2 tempPos = player->GetAnimRect()->GetPosition();
			out.write((char*)&tempPos, sizeof(tempPos));
			float tempSize = player->GetTotalSize();
			out.write((char*)&tempSize, sizeof(tempSize));
			
			// Boss
			int tempMaxHp = ribbyCroaks->GetMaxHp();
			out.write((char*)&tempMaxHp, sizeof(tempMaxHp));
			float tempDelay = ribbyCroaks->GetDelay();
			out.write((char*)&tempDelay, sizeof(tempDelay));

			// objectList
			int listSize = (int)objectList.size();
			out.write((char*)&listSize, sizeof(listSize));

			ForestObjectState tempObjectState;
			for (UINT i = 0; i < objectList.size(); ++i)
			{
				tempObjectState = objectList[i]->GetState();
				out.write((char*)&tempObjectState, sizeof(tempObjectState));
			}
		}
		out.close();
	}
}

void SceneRibbyCroaks::LoadRibbyCroaks(const wstring& path)
{
	if (path.empty())
	{
		function<void(wstring)> func = bind(&SceneRibbyCroaks::LoadRibbyCroaks, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::RibbyCroaksFilter, L"_Maps/", func, gHandle);
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

			// Boss
			int tempMaxHp;
			in.read((char*)&tempMaxHp, sizeof(tempMaxHp));
			ribbyCroaks->SetMaxHp(tempMaxHp);
			float tempDelay;
			in.read((char*)&tempDelay, sizeof(tempDelay));
			ribbyCroaks->SetDelay(tempDelay);

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
				else if (tempObjectState.type >= ForestObjectType::FPlatform_a && tempObjectState.type <= ForestObjectType::FPlatform_c)
					objectList[i] = make_shared<FloatingPlatform>(tempObjectState.type, tempObjectState.position, tempObjectState.totalSize, tempObjectState.rotation, tempObjectState.bCollision, tempObjectState.direction, tempObjectState.moveScale);
			}
		}
		in.close();
	}
}
