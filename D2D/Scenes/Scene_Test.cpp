#include "stdafx.h"
#include "Scene_Test.h"

void Scene::Init()
{
	player = make_unique<Player>(CENTER, Vector2(101, 159), 300.0f);
	ground = make_unique<ColorRect>(Vector2(CENTER_X, 100), Vector2(WIN_DEFAULT_WIDTH, 3), 0.0f, BLACK);

	ground->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void Scene::Destroy()
{
}

void Scene::Update()
{
	player->CheckGround(ground);

	player->Update();
	ground->Update();
}

void Scene::PreRender()
{
}

void Scene::Render()
{
	player->Render();
	ground->Render();
}

void Scene::PostRender()
{
}
