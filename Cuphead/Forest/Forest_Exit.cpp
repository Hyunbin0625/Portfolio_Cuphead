#include "stdafx.h"
#include "Forest_Exit.h"

Forest_Exit::Forest_Exit(const Vector2& position, const float& totalSize, float rotation, bool bCollision)
{
	// √ ±‚»≠
	nextScene = false;

	state = { ForestObjectType::Exit, position, totalSize, rotation, bCollision };

	textureRect = make_shared<TextureRect>(position, scale * totalSize, rotation, L"_Textures/Scene_ForestFollies/level_world_1_exit_sign.png");

	textureRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

bool Forest_Exit::Collision(shared_ptr<Player> player)
{
	if (textureRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
	{
		if (!nextScene)
			FIGHTTEXT->Init(FightTextType::RunNGun, false, true);
		nextScene = true;
	}

	return false;
}

void Forest_Exit::Update()
{
	if (bMod && !(ImGui::IsAnyItemActive()) && textureRect->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
	{
		state.position = INPUT->GetMousePosition();
		nextScene = false;
	}

	textureRect->SetPosition(state.position);
	textureRect->SetScale(scale * state.totalSize);
	textureRect->SetRotation((float)(state.rotation * 57.2));

	textureRect->Update();
}

void Forest_Exit::Render()
{
	textureRect->Render();
}

void Forest_Exit::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ". ExitSign";

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
