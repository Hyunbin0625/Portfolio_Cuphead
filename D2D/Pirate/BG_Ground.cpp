#include "stdafx.h"
#include "BG_Ground.h"

BG_Ground::BG_Ground(Vector2 position, Vector2 addTopPos, float size)
	: position(position), addPos(addTopPos), size(size)
{
	textureRect = make_unique<TextureRect>(position, Vector2(1015, 209) * size, 0.0f, L"_Textures/Pirate/pirateDockA.png");
	topTextureRect = make_unique<TextureRect>(position + addPos, Vector2(766, 89) * size, 0.0f, L"_Textures/Pirate/pirateDockB.png");
}

void BG_Ground::Update()
{
	textureRect->Update();
	topTextureRect->Update();
}

void BG_Ground::BRender()
{
	textureRect->Render();
}

void BG_Ground::FRender()
{
	topTextureRect->Render();
}

void BG_Ground::GUI()
{
	string objName = "Ground";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		textureRect->SetOutline(true);
		topTextureRect->SetOutline(true);

		ImGui::Text(objName.c_str());

		if (ImGui::InputFloat("Position.x", &position.x, 1.0f, 100.0f))
		{
			textureRect->SetPosition(position);
			topTextureRect->SetPosition(position + addPos);
		}
		if (ImGui::InputFloat("Position.y", &position.y, 1.0f, 100.0f))
		{
			textureRect->SetPosition(position);
			topTextureRect->SetPosition(position + addPos);
		}
		if (ImGui::InputFloat("AddPos.x", &addPos.x, 1.0f, 100.0f))
			topTextureRect->SetPosition(position + addPos);
		if (ImGui::InputFloat("AddPos.y", &addPos.y, 1.0f, 100.0f))
			topTextureRect->SetPosition(position + addPos);

		if (ImGui::InputFloat("Size", &size, 0.1f, 50.0f))
		{
			textureRect->SetScale(Vector2(1015, 209) * size);
			topTextureRect->SetScale(Vector2(766, 89) * size);
		}

		ImGui::EndMenu();
	}
	else
	{
		textureRect->SetOutline(false);
		topTextureRect->SetOutline(false);
	}
}
