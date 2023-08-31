#include "stdafx.h"
#include "Scenes/SceneList.h"
#include "Program.h"

int currentSceneIndex;

Program::Program()
{
}

void Program::Init()
{
	sceneList.push_back(make_shared<SceneMain>());
	sceneList.push_back(make_shared<SceneTutorial>());
	sceneList.push_back(make_shared<SceneForestFollies>());
	sceneList.push_back(make_shared<SceneRibbyCroaks>());
	sceneList.push_back(make_shared<ScenePirate>());
	sceneList.push_back(make_shared<Scene>());

	currentSceneIndex = 0;
	currentScene = sceneList[currentIndex];
	currentScene->Init();

	SOUND->AddSound("Noise", L"_Sounds/sfx_noise_1920s_01.wav", true);
	SOUND->SetVolume("Noise", 0.2f);
	SOUND->Play("Noise");
}

void Program::Update()
{
	if (currentIndex != currentSceneIndex)
	{
		currentIndex = currentSceneIndex;
		currentScene = sceneList[currentIndex];
		currentScene->Init();
	}

	CAMERA->Update();
	currentScene->Update();

	IRISA->Update();
	SCREENFX->Update();
}

void Program::PreRender()
{
	currentScene->PreRender();
}

void Program::Render()
{
	CAMERA->Render();
	currentScene->Render();

	IRISA->Render();
	SCREENFX->Render();
}

void Program::PostRender()
{
	currentScene->PostRender();

	IMGUI->PrintFrame();
}
