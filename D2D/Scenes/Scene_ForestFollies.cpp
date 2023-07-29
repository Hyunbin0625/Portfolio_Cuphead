#include "stdafx.h"
#include "Scene_ForestFollies.h"

void SceneForestFollies::Init()
{
	player = make_shared<Player>(CENTER, Vector2(101, 159), 500.0f, 3, 100.0f);

	skyLayer = make_unique<TextureRect>(CENTER, Vector2(1898, 823) * 1.35, 0.0f, L"_Textures/Scene_ForestFollies/lv1-1_bg_sky_01.png");

	ground = make_unique<ColorRect>(Vector2(5000, 300), Vector2(10000, 50), 0.0f, BLACK);
	ground->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void SceneForestFollies::Destroy()
{
}

void SceneForestFollies::Update()
{
	CheckGround();

	ground->Update();
	player->Update();
	UI->Init(CAMERA->GetPosition(), player->GetHp(), player->GetPercentSuperMeterCard());
	UI->Update();

	Vector2 temp = Vector2((player->GetAnimRect()->GetPosition().x - CENTER.x) - CAMERA->GetPosition().x, 0);
	CAMERA->SetPosition(Vector2(CAMERA->GetPosition().x + temp.x * 2 * DELTA, temp.y + 210));

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

	player->Render();

	UI->Render();
}

void SceneForestFollies::PostRender()
{
	player->GUI();
}

// 각 플렛폼에서 검사할 예정
void SceneForestFollies::CheckGround()
{
	player->SetCheckCollider(0);
	player->SetPlatform(0);
	if (ground->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= State::Special_Attack_R && player->GetState() <= State::Super_Beam_L))
	{
		player->SetGroundPos(Vector2(ground->GetPosition().x, ground->GetPosition().y + ground->GetScale().y / 2));
		player->SetCheckCollider(1);
		if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < ground->GetPosition().y + ground->GetScale().y / 2 - 1)
			player->GetAnimRect()->Move(Vector2(0, 100));
	}
}