#include "stdafx.h"
#include "Forest_Wall.h"

Forest_Wall::Forest_Wall(const Vector2& position, const float& totalSize, float rotation, bool bCollision)
{
	state = { ForestObjectType::Wall, position, totalSize, rotation, bCollision };

	textureRect = make_unique<TextureRect>(position, scale * totalSize, rotation, L"_Textures/wall.png");

	textureRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void Forest_Wall::Update()
{
	if (bMod)
	{
		if (!(ImGui::IsAnyItemActive()) && textureRect->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			state.position = INPUT->GetMousePosition();
	}

	textureRect->SetPosition(state.position);
	textureRect->SetScale(Vector2(scale.x, scale.y * state.totalSize));
	textureRect->SetRotation((float)(state.rotation * 57.2));

	textureRect->Update();
}

void Forest_Wall::Render()
{
	if (bCreateMod)
		textureRect->Render();
}

void Forest_Wall::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ". Wall";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		textureRect->SetOutline(true);

		ImGui::Text(objName.c_str());

		ImGui::SliderFloat2("Position", (float*)&state.position, CAMERA->GetPosition().x, CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH);
		ImGui::InputFloat("Size", &state.totalSize, 1.0f, 50.0f);
		ImGui::SliderAngle("Rotation", &state.rotation);

		ImGui::Checkbox("collision", &state.bCollision);

		if (ImGui::Button("Delete", ImVec2(50, 30)))
			bDelete = 1;

		ImGui::EndMenu();
	}
	else
	{
		textureRect->SetOutline(false);
	}
}
