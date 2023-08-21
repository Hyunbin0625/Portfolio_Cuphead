#include "stdafx.h"
#include "BG_Cloud.h"

BG_Cloud::BG_Cloud(CloudType type, Vector2 position, float speed, float size)
	: type(type), position(position), speed(speed), size(size)
{
	textureRectList.resize(2);
	for (int i = 0; i < textureRectList.size(); ++i)
		textureRectList[i] = make_unique<TextureRect>(Vector2(position.x + i * 1024, position.y), Vector2(1024, 218) * size, 0.0f, L"_Textures/Pirate/pirate_clouds_A.png");
}

void BG_Cloud::Update()
{
	switch (type)
	{
	case CloudType::Clouds_A:
		path = "_Textures/Pirate/pirate_clouds_A.png";
		for (auto& textureRect : textureRectList)
			textureRect->SetScale(Vector2(1024, 218) * size);
		break;
	case CloudType::Clouds_B:
		path = "_Textures/Pirate/pirate_clouds_B.png";
		for (auto& textureRect : textureRectList)
			textureRect->SetScale(Vector2(1024, 269) * size);
		break;
	case CloudType::Clouds_C:
		path = "_Textures/Pirate/pirate_clouds_C.png";
		for (auto& textureRect : textureRectList)
			textureRect->SetScale(Vector2(1023, 315) * size);
		break;
	}

	for (auto& textureRect : textureRectList)
	{
		textureRect->Move(Vector2(-speed, 0));
		if (textureRect->GetPosition().x + textureRect->GetScale().x * 0.5f <= CAMERA->GetPosition().x - 100)
			textureRect->SetPosition(Vector2(textureRect->GetPosition().x + textureRect->GetScale().x * 2, textureRect->GetPosition().y));
	}

	if (textureRectList[0]->GetPosition().x < textureRectList[1]->GetPosition().x)
		textureRectList[1]->SetPosition(Vector2(textureRectList[0]->GetPosition().x + textureRectList[0]->GetScale().x, textureRectList[1]->GetPosition().y));
	else
		textureRectList[0]->SetPosition(Vector2(textureRectList[1]->GetPosition().x + textureRectList[1]->GetScale().x, textureRectList[0]->GetPosition().y));

	for (auto& textureRect : textureRectList)
		textureRect->Update();
}

void BG_Cloud::Render()
{
	for (auto& textureRect : textureRectList)
		textureRect->Render();
}

void BG_Cloud::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ".Cloud";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		for (auto& textureRect : textureRectList)
			textureRect->SetOutline(true);

		ImGui::Text(objName.c_str());

		if (ImGui::InputFloat("Position.x", &position.x, 1.0f, 100.0f))
		{
			for (auto& textureRect : textureRectList)
				textureRect->SetPosition(position);
		}		
		if (ImGui::InputFloat("Position.y", &position.y, 1.0f, 100.0f))
		{
			for (auto& textureRect : textureRectList)
				textureRect->SetPosition(position);
		}
		ImGui::InputFloat("Speed", &speed, 1.0f, 50.0f);
		ImGui::InputFloat("Size", &size, 0.1f, 50.0f);

		ImGui::EndMenu();
	}
	else
	{
		for (auto& textureRect : textureRectList)
			textureRect->SetOutline(false);
	}
}
