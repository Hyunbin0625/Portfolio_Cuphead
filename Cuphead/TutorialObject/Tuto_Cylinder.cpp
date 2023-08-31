#include "stdafx.h"
#include "Tuto_Cylinder.h"

Tuto_Cylinder::Tuto_Cylinder(const Vector2& position, const float& totalSize, float rotation, bool bCollision)
{
	state = { TutoType::Cylinder, position, totalSize, rotation, bCollision };

	textureRect = make_unique<TextureRect>(position, scale * totalSize, rotation, L"_Textures/Scene_Tutorial/tutorial_cylinder_1.png");
	collision = make_shared<ColorRect>(position + Vector2() * totalSize, colScale * totalSize, 0.0f, BLACK);

	collision->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void Tuto_Cylinder::Collision(shared_ptr<Player> player)
{
	if (collision->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= PlayerState::Special_Attack_R && player->GetState() <= PlayerState::Super_Beam_L))
	{
		// 충돌시 player가 object 위인 경우
		if ( player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 + 5 > collision->GetPosition().y + collision->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().x > collision->GetPosition().x - collision->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().x < collision->GetPosition().x + collision->GetScale().x / 2)
		{
			player->SetCheckCollider(true);
			if (bPlatform)
				player->SetPlatform(true);
			player->SetGroundPos(Vector2(collision->GetPosition().x, collision->GetPosition().y + collision->GetScale().y / 2));

			if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < collision->GetPosition().y + collision->GetScale().y / 2 - 1 && !bPlatform)
			{
				player->GetAnimRect()->Move(Vector2(0, 400));
			}
		}
		
		if (player->GetAnimRect()->GetPosition().y < collision->GetPosition().y - collision->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().x > collision->GetPosition().x - collision->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().x < collision->GetPosition().x + collision->GetScale().x / 2)
		{
			if (!bPlatform)
			{
				player->GetAnimRect()->Move(Vector2(0, player->GetJumpSpeed()));
				player->SetJumpSpeed(0.0f);
			}
		}

		if (!bPlatform)
		{
			// 충돌시 player가 object 옆인 경우
			if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < collision->GetPosition().y + collision->GetScale().y / 2
				|| player->GetAnimRect()->GetPosition().y + player->GetAnimRect()->GetScale().y / 2 < collision->GetPosition().y - collision->GetScale().y / 2)
			{
				if (player->GetAnimRect()->GetPosition().x + player->GetAnimRect()->GetScale().x / 2 > collision->GetPosition().x - collision->GetScale().x / 2
					&& player->GetAnimRect()->GetPosition().x < collision->GetPosition().x)
				{
					player->GetAnimRect()->Move(Vector2(-player->GetSpeed(), 0));
				}
				if (player->GetAnimRect()->GetPosition().x - player->GetAnimRect()->GetScale().x / 2 < collision->GetPosition().x + collision->GetScale().x / 2
					&& player->GetAnimRect()->GetPosition().x > collision->GetPosition().x)
				{
					player->GetAnimRect()->Move(Vector2(player->GetSpeed(), 0));
				}
			}
		}
	}
}

void Tuto_Cylinder::Update()
{
	if (bMod && !(ImGui::IsAnyItemActive()) && collision->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
		state.position = INPUT->GetMousePosition();

	textureRect->SetPosition(state.position);
	collision->SetPosition(state.position + Vector2() * state.totalSize);

	textureRect->SetScale(scale * state.totalSize);
	collision->SetScale(colScale * state.totalSize);

	textureRect->SetRotation((float)(state.rotation * 57.2));
	collision->SetRotation((float)(state.rotation * 57.2));

	textureRect->Update();
	collision->Update();
}

void Tuto_Cylinder::Render()
{
	textureRect->Render();

	if (bMod)
		collision->Render();
}

void Tuto_Cylinder::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ". Cylinder";

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
