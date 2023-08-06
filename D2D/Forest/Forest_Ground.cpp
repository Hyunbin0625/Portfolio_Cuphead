#include "stdafx.h"
#include "Forest_Ground.h"

Forest_Ground::Forest_Ground(const Vector2& position, const float& totalSize, float rotation, bool bCollision)
{
	state = { ForestObjectType::Ground, position, totalSize, rotation, bCollision };

	textureRect = make_unique<TextureRect>(position, scale * totalSize, rotation, L"_Textures/ground.png");

	textureRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}		

void Forest_Ground::Update()
{
	if (bMod)
	{
		if (!(ImGui::IsAnyItemActive()) && textureRect->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			state.position = INPUT->GetMousePosition();
	}

	textureRect->SetPosition(state.position);
	textureRect->SetScale(Vector2(scale.x * state.totalSize, scale.y));
	textureRect->SetRotation((float)(state.rotation * 57.2));

	textureRect->Update();
}

void Forest_Ground::Render()
{
	textureRect->Render();
}

void Forest_Ground::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ". Ground";

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

bool Forest_Ground::Collision(shared_ptr<Player> player)
{
	if (textureRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= PlayerState::Special_Attack_R && player->GetState() <= PlayerState::Super_Beam_L))
	{
		// 충돌시 player가 object 위인 경우
		if ( player->GetAnimRect()->GetPosition().y > textureRect->GetPosition().y + textureRect->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().x > textureRect->GetPosition().x - textureRect->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().x < textureRect->GetPosition().x + textureRect->GetScale().x / 2)
		{
			player->SetGroundPos(Vector2(textureRect->GetPosition().x, textureRect->GetPosition().y + textureRect->GetScale().y / 2));
	
			if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < textureRect->GetPosition().y + textureRect->GetScale().y / 2 - 1)
			{
				player->GetAnimRect()->Move(Vector2(0, 400));
			}
			return true;
		}	// 충돌시 player가 object 아래인 경우
		else if (player->GetAnimRect()->GetPosition().y < textureRect->GetPosition().y - textureRect->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().x > textureRect->GetPosition().x - textureRect->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().x < textureRect->GetPosition().x + textureRect->GetScale().x / 2)
		{
			player->GetAnimRect()->Move(Vector2(0, player->GetJumpSpeed()));
			player->SetJumpSpeed(0.0f);
			return false;
		}	// 충돌시 player가 object 옆인 경우
		else if (player->GetAnimRect()->GetPosition().x > textureRect->GetPosition().x + textureRect->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().y < textureRect->GetPosition().y + textureRect->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().y > textureRect->GetPosition().y - textureRect->GetScale().y / 2)
		{
			player->GetAnimRect()->Move(Vector2(player->GetSpeed(), 0));
			return false;
		}
		else if (player->GetAnimRect()->GetPosition().x < textureRect->GetPosition().x - textureRect->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().y < textureRect->GetPosition().y + textureRect->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().y > textureRect->GetPosition().y - textureRect->GetScale().y / 2)
		{
			player->GetAnimRect()->Move(Vector2(-player->GetSpeed(), 0));
			return false;
		}
	}
	return false;
}
