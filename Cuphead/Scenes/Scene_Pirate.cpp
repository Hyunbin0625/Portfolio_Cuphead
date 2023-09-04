#include "stdafx.h"
#include "Scene_Pirate.h"

void ScenePirate::Init()
{
	// √ ±‚»≠
	bIntro = false;

	player = make_shared<Player>(Vector2(250, 180), Vector2(101, 159), 500.0f, 3, 100.0f);
	player->SetTotalSize(1.0f);

	pirate = make_shared<Pirate>(PirateInfo{ Vector2(-18, 272), 1.04, 10.0f }, PirateInfo{ Vector2(1110, 225), 1.3f, 3.0f }, 500.0f, 0.7f);

	// backGround
	backGround = make_unique<TextureRect>(CENTER + Vector2(0, 90.0f), Vector2(1020, 360) * 1.5f, 0.0f, L"_Textures/Pirate/pirate_clouds_D.png");

	ground = make_unique<BG_Ground>(Vector2(401, 91), Vector2(-46, 7), 1.1f);

	cloudList.resize(3);
	cloudList[0] = make_unique<BG_Cloud>((CloudType)2, Vector2(CENTER_X, 560.0f), 70.0f, 1.5f);
	cloudList[1] = make_unique<BG_Cloud>((CloudType)1, Vector2(CENTER_X, 480.0f), 150.0f, 1.5f);
	cloudList[2] = make_unique<BG_Cloud>((CloudType)0, Vector2(CENTER_X, 390.0f), 250.0f, 1.5f);

	waterList.resize(4);
	waterList[0] = make_unique<BG_Water>((WaterType)0, Vector2(CENTER_X, -50), 1.3f);

	waterList[1] = make_unique<BG_Water>((WaterType)3, Vector2(CENTER_X, 118), 1.3f); 
	waterList[2] = make_unique<BG_Water>((WaterType)2, Vector2(CENTER_X, 45), 1.3f);
	waterList[3] = make_unique<BG_Water>((WaterType)1, Vector2(CENTER_X, 0), 1.3f);

	forestObjectSet = make_unique<ForestObjectSet>();
	objectList.push_back(make_shared<Forest_Ground>(Vector2(193.0f, 73.999f), 6.0f, 0.0f, true));

	CAMERA->SetPosition(Vector2());

	BARREL->SetMinMax(Vector2(CAMERA->GetPosition().x, ground->GetTextureRect()->GetPosition().x + ground->GetTextureRect()->GetScale().x * 0.5f));

	IRISA->Start();

	SOUND->AddSound("Back", L"_Sounds/MUS_Pirate.wav", true);
	SOUND->Play("Back");
}

void ScenePirate::Destroy()
{
}

void ScenePirate::Update()
{
	// Intro
	if (!mod && IRISA->GetIsAnimEnd() && !bIntro)
	{
		bIntro = true;
		player->SetIntro(true);
		pirate->SetIntro(true);
		FIGHTTEXT->Init(FightTextType::Boss_B, true);
	}

	if (mod)
	{
		bIntro = false;
	}

	Collision();

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
	if (pirate->GetHp() <= 0)
	{
		deltaTime += DELTA;
		if (deltaTime <= 1.0f)
			FIGHTTEXT->Init(FightTextType::Boss_B, false, true);

		if ((int)deltaTime == 5)
			IRISA->End();

		if (deltaTime >= 5 && IRISA->GetIsAnimEnd())
		{
			deltaTime = 0.0f;
			pirate->Destroy();
			SOUND->DeleteSound("Back");
			currentSceneIndex = 0;
		}
	}

	backGround->Update();
	ground->Update();

	// ObjectList Update
	for (const auto& object : objectList)
		object->Update();

	// CloudList Update
	for (const auto& cloud : cloudList)
		cloud->Update();

	// WaterList Update
	for (const auto& water : waterList)
		water->Update();

	// CAMERA
	if (!mod)
		CAMERA->SetPosition(Vector2());
	
	player->Update();
	pirate->Update();
	UI->Init(CAMERA->GetPosition(), player->GetHp(), player->GetPercentSuperMeterCard());
	UI->Update();

	CAMERA->Update();
	if (bIntro)
		BARREL->Update();
	INKSCREEN->Update();
	FIGHTTEXT->Update();
}

void ScenePirate::PreRender()
{
}

void ScenePirate::Render()
{
	CAMERA->Render();
	backGround->Render();
	for (const auto& cloud : cloudList)
		cloud->Render();
	pirate->BRender();
	for (int i = 1; i < waterList.size() - 1; ++i)
		waterList[i]->Render();
	SHARK->ItRender();
	waterList.back()->Render();
	SQUID->Render();
	ground->BRender();
	{
		pirate->Render();
		DOGFISH->Render();
		SHARK->Render();
	
		BARREL->Render();

		player->Render();

		SQUIDBULLETMANAGER->Render();
	}
	ground->FRender();
	waterList.front()->Render();
	if (mod)
	{
		for (const auto& object : objectList)
			object->Render();
	}

	INKSCREEN->Render();
	UI->Render();
	FIGHTTEXT->Render();
}

void ScenePirate::PostRender()
{
	player->GUI();
	pirate->GUI();
	forestObjectSet->GUI();
	IMGUI->ForestObjectGUIS(objectList, "Object");

	static bool bOpen = true;
	if (ImGui::Begin("BackGroundMenu", &bOpen))
	{
		for (int i = 0; i < cloudList.size(); ++i)
			cloudList[i]->GUI(i);

		for (int i = 0; i < waterList.size(); ++i)
			waterList[i]->GUI(i);

		ground->GUI();
	}
	ImGui::End();

	if (ImGui::Begin("SubMonsterMenu", &bOpen))
	{
		BARREL->GUI();
		SHARK->GUI();
		DOGFISH->GUI();
		SQUID->GUI();
	}
	ImGui::End();

	if (ImGui::Begin("PirateScene", &bOpen))
	{
		if (ImGui::Button("Save", ImVec2(50, 30)))
			SaveRibbyCroaks();
		ImGui::SameLine();
		if (ImGui::Button("Load", ImVec2(50, 30)))
			LoadRibbyCroaks();

		if (ImGui::Checkbox("CreateMod", &mod))
		{
			for (const auto& object : objectList)
				object->SetMod(mod);
			player->SetMod(mod);
			pirate->SetMod(mod);
			BARREL->SetIsMod(mod);
		}
	}
	ImGui::End();
}

void ScenePirate::Collision()
{
	player->SetCheckCollider(false);
	player->SetPlatform(false);

	// Player&Enemies Collision
	pirate->Collision(player);

	// PeaBullet&Player
	for (int i = 0; i < PEABULLETMANAGER->GetBullets().size(); ++i)
	{
		if (PEABULLETMANAGER->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider))
			&& !PEABULLETMANAGER->GetBullets()[i]->GetDeath())
		{
			if (PEABULLETMANAGER->GetBullets()[i]->GetParrySlap())
			{
				parryTime += DELTA;
				if (parryTime < 0.5f && player->GetParry())
				{
					player->SetJumpSpeed(400.0f);
					player->SetVel(0.0f);
					player->SetSuperMeterCard((float)(player->GetSuperMeterCard() + 0.2 * player->GetMaxSuperMeterCard()));
					PEABULLETMANAGER->GetBullets()[i]->SetDeath(true);
					parryTime = 0.0f;
				}
				else if (parryTime >= 0.5f)
				{
					player->SetHit(true);
					PEABULLETMANAGER->GetBullets()[i]->SetDeath(true);
					parryTime = 0.0f;
				}
			}
			else
			{
				PEABULLETMANAGER->GetBullets()[i]->SetDeath(true);
				player->SetHit(true);
			}
		}
		else
		{
			for (auto& object : objectList)
			{
				if (object->GetState().type == ForestObjectType::Ground)
				{
					if (PEABULLETMANAGER->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(object->GetTextureRect()->GET_COMP(Collider))
						&& !PEABULLETMANAGER->GetBullets()[i]->GetDeath())
						PEABULLETMANAGER->GetBullets()[i]->SetDeath(true);
				}
			}
		}
	}

	// CannonBullet&Player
	for (int i = 0; i < CANNONBALLMANAGER->GetBullets().size(); ++i)
	{
		if (CANNONBALLMANAGER->GetBullets()[i]->GetColorRect()->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
			player->SetHit(true);
	}

	// Barrel&Object Collision
	for (auto& object : objectList)
	{
		if (object->GetCollision() && BARREL->GetDrop())
		{
			if (BARREL->GetAnimRect()->GET_COMP(Collider)->Intersect(object->GetTextureRect()->GET_COMP(Collider)))
			{
				BARREL->SetDrop(false);
				BARREL->SetSmash(true);
			}
		}
	}
	BARREL->Collision(player);

	// Shark&Player
	SHARK->Collision(player);

	// DogFish&Ground
	for (auto& object : objectList)
	{
		if (object->GetState().type == ForestObjectType::Ground)
		{
			for (auto& dogFish : DOGFISH->GetDogFishList())
				if (object->GetTextureRect()->GET_COMP(Collider)->Intersect(dogFish->GetAnimRect()->GET_COMP(Collider)))
					dogFish->SetGround(object->GetTextureRect()->GetPosition().y + object->GetTextureRect()->GetScale().y * 0.5f);
		}
	}
	// DogFish&Player
	DOGFISH->Collision(player);

	// SquidBulletManager&Ground
	for (auto& object : objectList)
	{
		if (object->GetState().type == ForestObjectType::Ground)
		{
			for (auto& squidBullet : SQUIDBULLETMANAGER->GetSquidBulletList())
				if (object->GetTextureRect()->GET_COMP(Collider)->Intersect(squidBullet->GetAnimRect()->GET_COMP(Collider)))
					squidBullet->SetEnd(true);
		}
	}
	// SquidBulletManager&Player
	SQUIDBULLETMANAGER->Collision(player);

	// PirateBeam&Player
	if (PIRATEBEAM->GetCollisionRect()->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
		player->SetHit(true);

	// PirateBubbleManager&Player
	for (auto& bubble : BUBBLEMANAGER->GetBullets())
	{
		if (bubble->GetActivation() && bubble->GetAnimRect()->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
		{
			player->SetHit(true);
			bubble->SetIsEnd(true);
		}
	}

	// Player&Object Collision
	for (auto& object : objectList)
	{
		if (object->GetCollision())
		{
			if (object->Collision(player))
				player->SetCheckCollider(true);
		}
	}
}

void ScenePirate::SaveRibbyCroaks(const wstring& path)
{
	if (path.empty())
	{
		function<void(wstring)> func = bind(&ScenePirate::SaveRibbyCroaks, this, placeholders::_1);
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

void ScenePirate::LoadRibbyCroaks(const wstring& path)
{
	if (path.empty())
	{
		function<void(wstring)> func = bind(&ScenePirate::LoadRibbyCroaks, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::RibbyCroaksFilter, L"_Maps/", func, gHandle);
	}
	else
	{
		ifstream in(path.c_str());

		if (in.is_open())
		{
			// Player
			Vector2 tempPos = Vector2();
			in.read((char*)&tempPos, sizeof(tempPos));
			player->SetPosition(tempPos);
			float tempSize = 0.0f;
			in.read((char*)&tempSize, sizeof(tempSize));
			player->SetTotalSize(tempSize);

			// Boss

			// ObjectList
			int listSize = 0;
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
