#include "stdafx.h"
#include "Tuto_Platform.h"

Tuto_Platform::Tuto_Platform(const Vector2& position, const float& totalSize, float rotation, bool bCollision)
{
	state = { TutoType::Platform, position, totalSize, rotation, bCollision };

	textureRect = make_unique<TextureRect>(position, scale * totalSize, rotation, L"_Textures/Scene_Tutorial/tutorial_cylinder_and_platform.png");
	collisionRect = make_shared<ColorRect>(position + Vector2(-490, -320) * state.totalSize, colScaleR * totalSize, 0.0f, BLACK);
	collisionPlat = make_shared<ColorRect>(position + Vector2(60, -45) * state.totalSize, colScaleP * totalSize, 0.0f, BLACK);
	collisionCircle = make_shared<ColorRect>(position + Vector2(520, 320) * state.totalSize, colScaleC * totalSize, 0.0f, BLACK);

	textureRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
	collisionRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
	collisionPlat->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
	collisionCircle->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void Tuto_Platform::Collision(shared_ptr<Player> player)
{
	if (collisionRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= PlayerState::Special_Attack_R && player->GetState() <= PlayerState::Super_Beam_L))
	{
		// 충돌시 player가 object 위인 경우
		if ( player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 + 5 > collisionRect->GetPosition().y + collisionRect->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().x > collisionRect->GetPosition().x - collisionRect->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().x < collisionRect->GetPosition().x + collisionRect->GetScale().x / 2)
		{
			player->SetCheckCollider(true);
			player->SetGroundPos(Vector2(collisionRect->GetPosition().x, collisionRect->GetPosition().y + collisionRect->GetScale().y / 2));

			if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < collisionRect->GetPosition().y + collisionRect->GetScale().y / 2 - 1)
			{
				player->GetAnimRect()->Move(Vector2(0, 400));
			}
		}
		
		// 충돌시 player가 object 아래인 경우
		if (player->GetAnimRect()->GetPosition().y < collisionRect->GetPosition().y - collisionRect->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().x > collisionRect->GetPosition().x - collisionRect->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().x < collisionRect->GetPosition().x + collisionRect->GetScale().x / 2)
		{
			player->GetAnimRect()->Move(Vector2(0, player->GetJumpSpeed()));
			player->SetJumpSpeed(0.0f);
		}

		// 충돌시 player가 object 옆인 경우
		if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < collisionRect->GetPosition().y + collisionRect->GetScale().y / 2
			|| player->GetAnimRect()->GetPosition().y + player->GetAnimRect()->GetScale().y / 2 < collisionRect->GetPosition().y - collisionRect->GetScale().y / 2)
		{
			if (player->GetAnimRect()->GetPosition().x + player->GetAnimRect()->GetScale().x / 2 > collisionRect->GetPosition().x - collisionRect->GetScale().x / 2
				&& player->GetAnimRect()->GetPosition().x < collisionRect->GetPosition().x)
			{
				player->GetAnimRect()->Move(Vector2(-player->GetSpeed(), 0));
			}
			if (player->GetAnimRect()->GetPosition().x - player->GetAnimRect()->GetScale().x / 2 < collisionRect->GetPosition().x + collisionRect->GetScale().x / 2
				&& player->GetAnimRect()->GetPosition().x > collisionRect->GetPosition().x)
			{
				player->GetAnimRect()->Move(Vector2(player->GetSpeed(), 0));
			}
		}
	}

	if (collisionPlat->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= PlayerState::Special_Attack_R && player->GetState() <= PlayerState::Super_Beam_L))
	{
		// 충돌시 player가 object 위인 경우
		if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 + 5 > collisionPlat->GetPosition().y + collisionPlat->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().x > collisionPlat->GetPosition().x - collisionPlat->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().x < collisionPlat->GetPosition().x + collisionPlat->GetScale().x / 2)
		{
			player->SetCheckCollider(true);
			if (bPlatform)
				player->SetPlatform(true);
			player->SetGroundPos(Vector2(collisionPlat->GetPosition().x, collisionPlat->GetPosition().y + collisionPlat->GetScale().y / 2));

			if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < collisionPlat->GetPosition().y + collisionPlat->GetScale().y / 2 - 1 && !bPlatform)
			{
				player->GetAnimRect()->Move(Vector2(0, 400));
			}
		}

		// 충돌시 player가 object 아래인 경우
		if (player->GetAnimRect()->GetPosition().y < collisionPlat->GetPosition().y - collisionPlat->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().x > collisionPlat->GetPosition().x - collisionPlat->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().x < collisionPlat->GetPosition().x + collisionPlat->GetScale().x / 2)
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
			if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < collisionPlat->GetPosition().y + collisionPlat->GetScale().y / 2
				|| player->GetAnimRect()->GetPosition().y + player->GetAnimRect()->GetScale().y / 2 < collisionPlat->GetPosition().y - collisionPlat->GetScale().y / 2)
			{
				if (player->GetAnimRect()->GetPosition().x + player->GetAnimRect()->GetScale().x / 2 > collisionPlat->GetPosition().x - collisionPlat->GetScale().x / 2
					&& player->GetAnimRect()->GetPosition().x < collisionPlat->GetPosition().x)
				{
					player->GetAnimRect()->Move(Vector2(-player->GetSpeed(), 0));
				}
				if (player->GetAnimRect()->GetPosition().x - player->GetAnimRect()->GetScale().x / 2 < collisionPlat->GetPosition().x + collisionPlat->GetScale().x / 2
					&& player->GetAnimRect()->GetPosition().x > collisionPlat->GetPosition().x)
				{
					player->GetAnimRect()->Move(Vector2(player->GetSpeed(), 0));
				}
			}
		}
	}

	if (collisionCircle->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= PlayerState::Special_Attack_R && player->GetState() <= PlayerState::Super_Beam_L))
	{
		// 충돌시 player가 object 위인 경우
		if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 + 5 > collisionCircle->GetPosition().y + collisionCircle->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().x > collisionCircle->GetPosition().x - collisionCircle->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().x < collisionCircle->GetPosition().x + collisionCircle->GetScale().x / 2)
		{
			player->SetCheckCollider(true);
			player->SetGroundPos(Vector2(collisionCircle->GetPosition().x, collisionCircle->GetPosition().y + collisionCircle->GetScale().y / 2));

			if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < collisionCircle->GetPosition().y + collisionCircle->GetScale().y / 2 - 1)
			{
				player->GetAnimRect()->Move(Vector2(0, 400));
			}
		}

		// 충돌시 player가 object 아래인 경우
		if (player->GetAnimRect()->GetPosition().y < collisionCircle->GetPosition().y - collisionCircle->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().x > collisionCircle->GetPosition().x - collisionCircle->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().x < collisionCircle->GetPosition().x + collisionCircle->GetScale().x / 2)
		{
			player->GetAnimRect()->Move(Vector2(0, player->GetJumpSpeed()));
			player->SetJumpSpeed(0.0f);
		}

		// 충돌시 player가 object 옆인 경우
		if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < collisionCircle->GetPosition().y + collisionCircle->GetScale().y / 2
			|| player->GetAnimRect()->GetPosition().y + player->GetAnimRect()->GetScale().y / 2 < collisionCircle->GetPosition().y - collisionCircle->GetScale().y / 2)
		{
			if (player->GetAnimRect()->GetPosition().x + player->GetAnimRect()->GetScale().x / 2 > collisionCircle->GetPosition().x - collisionCircle->GetScale().x / 2
				&& player->GetAnimRect()->GetPosition().x < collisionCircle->GetPosition().x)
			{
				player->GetAnimRect()->Move(Vector2(-player->GetSpeed(), 0));
			}
			if (player->GetAnimRect()->GetPosition().x - player->GetAnimRect()->GetScale().x / 2 < collisionCircle->GetPosition().x + collisionCircle->GetScale().x / 2
				&& player->GetAnimRect()->GetPosition().x > collisionCircle->GetPosition().x)
			{
				player->GetAnimRect()->Move(Vector2(player->GetSpeed(), 0));
			}
		}
	}
}

void Tuto_Platform::Update()
{
	if (bMod && !(ImGui::IsAnyItemActive()) && textureRect->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
		state.position = INPUT->GetMousePosition();

	textureRect->SetPosition(state.position);
	collisionRect->SetPosition(state.position + Vector2(-490, -320) * state.totalSize);
	collisionPlat->SetPosition(state.position + Vector2(60, -45) * state.totalSize);
	collisionCircle->SetPosition(state.position + Vector2(520, 320) * state.totalSize);

	textureRect->SetScale(scale * state.totalSize);
	collisionRect->SetScale(colScaleR * state.totalSize);
	collisionPlat->SetScale(colScaleP * state.totalSize);
	collisionCircle->SetScale(colScaleC * state.totalSize);

	textureRect->SetRotation((float)(state.rotation * 57.2));
	collisionRect->SetRotation((float)(state.rotation * 57.2));
	collisionPlat->SetRotation((float)(state.rotation * 57.2));
	collisionCircle->SetRotation((float)(state.rotation * 57.2));

	textureRect->Update();
	collisionRect->Update();
	collisionPlat->Update();
	collisionCircle->Update();
}

void Tuto_Platform::Render()
{
	textureRect->Render();

	if (bMod)
	{
		collisionRect->Render();
		collisionPlat->Render();
		collisionCircle->Render();
	}
}

void Tuto_Platform::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ". Platform";

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
