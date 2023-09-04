#include "stdafx.h"
#include "Tuto_ExitDoor.h"

Tuto_ExitDoor::Tuto_ExitDoor(const Vector2& position, const float& totalSize, float rotation, bool bCollision)
{
	state = { TutoType::ExitDoor, position, totalSize, rotation, bCollision };

	textureRect = make_unique<TextureRect>(position, scale * totalSize, rotation, L"_Textures/Scene_Tutorial/tutorial_exit_door.png");

	textureRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void Tuto_ExitDoor::Collision(shared_ptr<Player> player)
{
	if (textureRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
	{
		if (INPUT->Press('Z') && !nextScene)
		{
			nextScene = true;
			IRISA->End();
		}
	}
}

void Tuto_ExitDoor::Update()
{
	if (bMod && !(ImGui::IsAnyItemActive()) && textureRect->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
		state.position = INPUT->GetMousePosition();

	textureRect->SetPosition(state.position);
	textureRect->SetScale(scale * state.totalSize);
	textureRect->SetRotation((float)(state.rotation * 57.2));

	if (nextScene && IRISA->GetIsAnimEnd())
	{
		nextScene = false;
		SOUND->DeleteSound("Back");
		++currentSceneIndex;
	}

	textureRect->Update();
}

void Tuto_ExitDoor::Render()
{
	textureRect->Render();
}

void Tuto_ExitDoor::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ". ExitDoor";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		textureRect->SetOutline(true);

		ImGui::Text(objName.c_str());

		ImGui::SliderFloat2("Position", (float*)&state.position, CAMERA->GetPosition().x, CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH);
		ImGui::SliderFloat("Size", &state.totalSize, 0.1f, 5.0f, "%.2f");
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
