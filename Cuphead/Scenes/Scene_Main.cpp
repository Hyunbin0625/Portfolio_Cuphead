#include "stdafx.h"
#include "Scene_Main.h"

void SceneMain::Init()
{
	// √ ±‚»≠
	CurrentButton = 0;
	bStart = false;
	bMod = false;
	bOption = false;
	bEnd = false;

	background = make_unique<TextureRect>(Vector2(CENTER_X, CENTER_Y - 10), Vector2(WIN_DEFAULT_WIDTH, WIN_DEFAULT_HEIGHT) * 1.2, 0.0f, L"_Textures/Scene_Main/cuphead_secondary_title_screen.png");

	startButton = make_unique<TextureRect>(Vector2(CENTER_X, CENTER_Y + 47 * 2 * 0.7), Vector2(80, 45) * 0.7, 0.0f, L"_Textures/Scene_Main/start_00.png");
	modButton = make_unique<TextureRect>(Vector2(CENTER_X, CENTER_Y + 47 * 0.7), Vector2(80, 45) * 0.7, 0.0f, L"_Textures/Scene_Main/mod_00.png");
	optionButton = make_unique<TextureRect>(Vector2(CENTER_X - 1, CENTER_Y), Vector2(78, 43) * 0.7, 0.0f, L"_Textures/Scene_Main/option_00.png");
	endButton = make_unique<TextureRect>(Vector2(CENTER_X, CENTER_Y - 47 * 0.7), Vector2(80, 45) * 0.7, 0.0f, L"_Textures/Scene_Main/end_00.png");

	CAMERA->SetPosition(Vector2());

	IRISA->Start();

	SOUND->DeleteSound("Back");
	SOUND->AddSound("Back", L"_Sounds/MUS_Intro_DontDealWithDevil_Vocal.wav", true);
	SOUND->Play("Back");
}

void SceneMain::Destroy()
{
}

void SceneMain::Update()
{
	if (INPUT->Down(VK_DOWN))
		++CurrentButton;
	else if (INPUT->Down(VK_UP))
		--CurrentButton;

	if (CurrentButton > 3)
		CurrentButton = 0;
	else if (CurrentButton < 0)
		CurrentButton = 3;

	wstring path = L"_Textures/Scene_Main/start_00.png";
	startButton->SetSRV(path);
	path = L"_Textures/Scene_Main/mod_00.png";
	modButton->SetSRV(path);
	path = L"_Textures/Scene_Main/option_00.png";
	optionButton->SetSRV(path);
	path = L"_Textures/Scene_Main/end_00.png";
	endButton->SetSRV(path);

	switch ((Button)CurrentButton)
	{
	case Button::Start:
		path = L"_Textures/Scene_Main/start_01.png";
		startButton->SetSRV(path);
		if (INPUT->Down(VK_RETURN) || INPUT->Down('Z') && !bStart)
		{
			bStart = true;
			bCreateMod = false;
			IRISA->End();
		}
		break;
	case Button::Mod:
		path = L"_Textures/Scene_Main/mod_01.png";
		modButton->SetSRV(path);
		if (INPUT->Down(VK_RETURN) || INPUT->Down('Z'))
		{
			bMod = true;
			bCreateMod = true;
			IRISA->End();
		}
		break;
	case Button::Option:
		path = L"_Textures/Scene_Main/option_01.png";
		optionButton->SetSRV(path);
		if (INPUT->Down(VK_RETURN) || INPUT->Down('Z'))
			bOption = true;
		break;
	case Button::End:
		path = L"_Textures/Scene_Main/end_01.png";
		endButton->SetSRV(path);
		if (INPUT->Down(VK_RETURN) || INPUT->Down('Z'))
		{
			bEnd = true;
			PostMessage(gHandle, WM_QUIT, 0, 0);
		}
		break;
	}

	if (bStart && IRISA->GetIsAnimEnd())
	{
		bStart = false;
		SOUND->DeleteSound("Back");
		currentSceneIndex += 1;
	}
	else if (bMod && IRISA->GetIsAnimEnd())
	{
		bMod = false;
		SOUND->DeleteSound("Back");
		currentSceneIndex += 1;
	}

	background->Update();

	startButton->Update();
	modButton->Update();
	optionButton->Update();
	endButton->Update();
}

void SceneMain::PreRender()
{
}

void SceneMain::Render()
{
	background->Render();

	startButton->Render();
	modButton->Render();
	optionButton->Render();
	endButton->Render();
}

void SceneMain::PostRender()
{
}
