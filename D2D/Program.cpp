#include "stdafx.h"
#include "Scenes/SceneList.h"
#include "Program.h"

Program::Program()
{
}

void Program::Init()
{
	sceneList.push_back(make_shared<SceneMain>());
	sceneList.push_back(make_shared<SceneTutorial>());
	sceneList.push_back(make_shared<SceneForestFollies>());
	sceneList.push_back(make_shared<SceneRibbyCroaks>());
	sceneList.push_back(make_shared<Scene>());

	currentScene = sceneList[3];
	currentScene->Init();
}

void Program::Update()
{
//	if (dynamic_pointer_cast<SceneMain>(sceneList[0])->GetStart())
//	{
//		dynamic_pointer_cast<SceneMain>(sceneList[0])->Reset();
//		currentScene = sceneList[1];
//		currentScene->Init();
//	}

	CAMERA->Update();
	currentScene->Update();
}

void Program::PreRender()
{
	currentScene->PreRender();
}

void Program::Render()
{
	CAMERA->Render();

	currentScene->Render();
}

void Program::PostRender()
{
	currentScene->PostRender();

	IMGUI->PrintFrame();
}
