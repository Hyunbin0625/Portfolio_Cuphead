#include "stdafx.h"
#include "Scene_Test.h"

void Scene::Init()
{
	player = make_shared<Player>(CENTER, Vector2(101, 159), 500.0f, 3, 100.0f);
	ground = make_unique<ColorRect>(Vector2(CENTER_X, 100), Vector2(WIN_DEFAULT_WIDTH, 3), 0.0f, BLACK);
	ground2 = make_unique<ColorRect>(Vector2(CENTER_X, 300), Vector2(300, 3), 0.0f, BLACK);

	sphere = make_unique<Sphere>(Vector2(1100, 300), Vector2(48, 48), 0.0f, true);

	// AddComponent
	ground->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
	ground2->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void Scene::Destroy()
{
}

void Scene::Update()
{
	CheckGround();

	player->Update();
	UI->Init(CAMERA->GetPosition(), player->GetHp(), player->GetPercentSuperMeterCard());
	UI->Update();

	Vector2 temp = (player->GetAnimRect()->GetPosition() - CENTER) - CAMERA->GetPosition();
	CAMERA->SetPosition(CAMERA->GetPosition() + temp * 2 * DELTA);

	ground->Update();
	ground2->Update();

	sphere->Update();

	sphere->CheckCollision(player);
}

void Scene::PreRender()
{
}

void Scene::Render()
{
	ground->Render();
	ground2->Render();
	sphere->Render();
	player->Render();

	UI->Render();
}

void Scene::PostRender()
{
	player->GUI();
	sphere->GUI();
}

// 각 플렛폼에서 검사할 예정
void Scene::CheckGround()
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

	if (ground2->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= PlayerState::Special_Attack_R && player->GetState() <= PlayerState::Super_Beam_L))
	{
		player->SetGroundPos(Vector2(ground2->GetPosition().x, ground2->GetPosition().y + ground2->GetScale().y / 2));
		player->SetCheckCollider(1);
		player->SetPlatform(1);
		if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < ground2->GetPosition().y + ground2->GetScale().y / 2 - 1)
			player->GetAnimRect()->Move(Vector2(0, 100));
	}
}
