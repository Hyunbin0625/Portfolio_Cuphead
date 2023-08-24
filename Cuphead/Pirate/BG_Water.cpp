#include "stdafx.h"
#include "BG_Water.h"

BG_Water::BG_Water(WaterType type, Vector2 position, float size)
	: type(type), position(position), size(size)
{
	animRect = make_unique<AnimationRect>(position, Vector2(1023, 294) * size, 0.0f, L"_Textures/Pirate/pirate_WaterA_01.png");

	switch (type)
	{
	case WaterType::Water_A:
		typeName = L"WaterA_0";
		break;
	case WaterType::Water_B:
		typeName = L"WaterB_0";
		break;
	case WaterType::Water_C:
		typeName = L"WaterC_0";
		break;
	case WaterType::Water_D:
		typeName = L"WaterD_0";
		break;
	}

	for (int i = 1; i < 6; ++i)
		animRect->AddAnimClip(make_shared<AnimationClip>(L"Water_0" + to_wstring(i), L"_Textures/Pirate/pirate_" + typeName + to_wstring(i) + L".png", 10, false, false, 0.1));
	
	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));
}

void BG_Water::Update()
{
	switch (type)
	{
	case WaterType::Water_A:
		animRect->SetScale(Vector2(1023, 294) * size);
		break;
	case WaterType::Water_B:
		animRect->SetScale(Vector2(1024, 269) * size);
		break;
	case WaterType::Water_C:
		animRect->SetScale(Vector2(1023, 315) * size);
		break;
	}
	animRect->SetPosition(Vector2(position.x, position.y + animRect->GetScale().y * 0.5f));

	if (currentClip == 0)
	{
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Water_01");
		if (animRect->GET_COMP(Animator)->GetEnd())
			++currentClip;
	}
	else if (currentClip == 1)
	{
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Water_02");
		if (animRect->GET_COMP(Animator)->GetEnd())
			++currentClip;
	}
	else if (currentClip == 2)
	{
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Water_03");
		if (animRect->GET_COMP(Animator)->GetEnd())
			++currentClip;
	}
	else if (currentClip == 3)
	{
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Water_04");
		if (animRect->GET_COMP(Animator)->GetEnd())
			++currentClip;
	}
	else if (currentClip == 4)
	{
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Water_05");
		if (animRect->GET_COMP(Animator)->GetEnd())
			currentClip = 0;
	}

	animRect->Update();
}

void BG_Water::Render()
{
	animRect->Render();
}

void BG_Water::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ".Water";

	if (ImGui::BeginMenu(objName.c_str()))
	{
			animRect->SetOutline(true);

		ImGui::Text(objName.c_str());

		if (ImGui::InputFloat("Position.x", &position.x, 1.0f, 100.0f))
			animRect->SetPosition(Vector2(position.x, position.y + animRect->GetScale().y * 0.5f));
		if (ImGui::InputFloat("Position.y", &position.y, 1.0f, 100.0f))
			animRect->SetPosition(position);
		ImGui::InputFloat("Size", &size, 0.1f, 50.0f);

		ImGui::EndMenu();
	}
	else
	{
		animRect->SetOutline(false);
	}
}
