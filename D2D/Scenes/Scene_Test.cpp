#include "stdafx.h"
#include "Scene_Test.h"

void Scene::Init()
{
	player = make_unique<Player>(CENTER, Vector2(101, 159), 300.0f);
	ground = make_unique<ColorRect>(Vector2(CENTER_X, 100), Vector2(WIN_DEFAULT_WIDTH, 3), 0.0f, BLACK);
	ground2 = make_unique<ColorRect>(Vector2(CENTER_X, 400), Vector2(300, 3), 0.0f, BLACK);

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

	ground->Update();
	ground2->Update();
}

void Scene::PreRender()
{
}

void Scene::Render()
{
	player->Render();
	ground->Render();
	ground2->Render();
}

void Scene::PostRender()
{
	player->GUI();
}

// 각 플렛폼에서 검사할 예정
void Scene::CheckGround()
{
	player->SetCheckCollider(0);
	player->SetPlatform(0);
	if (ground->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
	{
		player->SetCheckCollider(1);
		if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < ground->GetPosition().y + ground->GetScale().y / 2 - 2)
			player->GetAnimRect()->Move(Vector2(0, 400));
	}

	if (ground2->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
	{
		player->SetCheckCollider(1);
		player->SetPlatform(1);
		if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < ground2->GetPosition().y + ground2->GetScale().y / 2 - 2)
			player->GetAnimRect()->Move(Vector2(0, 400));
	}
}
