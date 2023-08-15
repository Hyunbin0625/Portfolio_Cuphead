#include "stdafx.h"
#include "FloatingPlatform.h"

FloatingPlatform::FloatingPlatform(ForestObjectType type, const Vector2& position, const float& totalSize, float rotation, bool bCollision, bool direction, float moveScale)
{
	state = { type, position, totalSize, rotation, bCollision, direction, moveScale };

	// TextureRect
	textureRect = make_shared<TextureRect>(position, Vector2(430, 112) * totalSize, rotation, L"_Textures/Scene_ForestFollies/lv1-1_mg_floating-platform-double.png");

	// Collision
	collision = make_shared<ColorRect>(position, Vector2(420, 78) * totalSize, 0.0f, BLACK);
	collision->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));

	// AnimRect
	animRect = make_shared<AnimationRect>(Vector2(position), Vector2(152, 55) * state.totalSize, 0.0f, L"_Textures/Scene_ForestFollies/platform_propellor.png");
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Propellor", L"_Textures/Scene_ForestFollies/platform_propellor.png", 9, false, true, 0.09));
	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));
}

bool FloatingPlatform::Collision(shared_ptr<Player> player)
{
	if (collision->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= PlayerState::Special_Attack_R && player->GetState() <= PlayerState::Super_Beam_L))
	{
		// 충돌시 player가 object 위인 경우
		if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 + 5 > collision->GetPosition().y + collision->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().x > collision->GetPosition().x - collision->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().x < collision->GetPosition().x + collision->GetScale().x / 2)
		{
		//	player->SetCheckCollider(true);
			if (bPlatform)
			{
				player->SetPlatform(true);
				if (!state.direction)	// 0 : 상하
				{
					if (!check)	// Up
						player->GetAnimRect()->Move(Vector2(0, 100));
					else		// Down
						player->GetAnimRect()->Move(Vector2(0, -100));
				}
				else		// 1 : 좌우
				{
					if (!check)	// Right
						player->GetAnimRect()->Move(Vector2(100, 0));
					else		// Left
						player->GetAnimRect()->Move(Vector2(-100, 0));
				}
			}
			player->SetGroundPos(Vector2(collision->GetPosition().x, collision->GetPosition().y + collision->GetScale().y / 2));

			if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < collision->GetPosition().y + collision->GetScale().y / 2 - 1 && !bPlatform)
				player->GetAnimRect()->Move(Vector2(0, 400));
			return true;
		}

		// 충돌시 player가 object 아래인 경우
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
	return false;
}

void FloatingPlatform::Update()
{
	if (bMod)
	{
		if (!(ImGui::IsAnyItemActive()) && collision->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			state.position = INPUT->GetMousePosition();

		textureRect->SetPosition(state.position);

		textureRect->SetRotation((float)(state.rotation * 57.2));
		collision->SetRotation((float)(state.rotation * 57.2));
		animRect->SetRotation((float)(state.rotation * 57.2));
	}

	switch (state.type)
	{
	case ForestObjectType::FPlatform_a:
		// Scale
		textureRect->SetScale(Vector2(430, 112) * state.totalSize);
		collision->SetScale(Vector2(420, 78) * state.totalSize);
		animRect->SetScale(Vector2(152, 55) * state.totalSize);
		// Position
		collision->SetPosition(Vector2(textureRect->GetPosition().x, textureRect->GetPosition().y - 10 * state.totalSize));
		animRect->SetPosition(Vector2(textureRect->GetPosition().x, textureRect->GetPosition().y - 53 * state.totalSize));
		// SRV
		path = L"_Textures/Scene_ForestFollies/lv1-1_mg_floating-platform-double.png";
		textureRect->SetSRV(path);
		break;
	case ForestObjectType::FPlatform_b:
		// Scale
		textureRect->SetScale(Vector2(188, 115) * state.totalSize);
		collision->SetScale(Vector2(183, 74) * state.totalSize);
		animRect->SetScale(Vector2(152, 55) * state.totalSize);
		// Position
		collision->SetPosition(Vector2(textureRect->GetPosition().x, textureRect->GetPosition().y - 15 * state.totalSize));
		animRect->SetPosition(Vector2(textureRect->GetPosition().x, textureRect->GetPosition().y - 55 * state.totalSize));
		// SRV
		path = L"_Textures/Scene_ForestFollies/lv1-1_mg_floating-platform-single_0001.png";
		textureRect->SetSRV(path);
		break;
	case ForestObjectType::FPlatform_c:
		// Scale
		textureRect->SetScale(Vector2(187, 112) * state.totalSize);
		collision->SetScale(Vector2(178, 75) * state.totalSize);
		animRect->SetScale(Vector2(152, 55) * state.totalSize);
		// Position
		collision->SetPosition(Vector2(textureRect->GetPosition().x, textureRect->GetPosition().y - 10 * state.totalSize));
		animRect->SetPosition(Vector2(textureRect->GetPosition().x, textureRect->GetPosition().y - 55 * state.totalSize));
		// SRV
		path = L"_Textures/Scene_ForestFollies/lv1-1_mg_floating-platform-single_0002.png";
		textureRect->SetSRV(path);
		break;
	}

	Move();

	animRect->Update();
	textureRect->Update();
	collision->Update();
}

void FloatingPlatform::Render()
{
	animRect->Render();
	textureRect->Render();
	if (bMod)
		collision->Render();
}

void FloatingPlatform::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ". FloatingPlatform";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		textureRect->SetOutline(true);

		ImGui::Text(objName.c_str());

		bool a = 0, b = 0, c = 0;
		if (state.type == ForestObjectType::FPlatform_a)
			a = true;
		else if (state.type == ForestObjectType::FPlatform_b)
			b = true;
		else
			c = true;

		ImGui::Text("Type");
		if (ImGui::Checkbox("A", &a))
		{
			state.type = ForestObjectType::FPlatform_a;
			b, c = false;
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("B", &b))
		{
			state.type = ForestObjectType::FPlatform_b;
			a, c = false;
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("C", &c))
		{
			state.type = ForestObjectType::FPlatform_c;
			a, b = false;
		}

		ImGui::SliderFloat2("Position", (float*)&state.position, CAMERA->GetPosition().x, CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH);
		ImGui::SliderFloat("Size", &state.totalSize, 0.1f, 5.0f, "%.2f");
		ImGui::SliderAngle("Rotation", &state.rotation);

		ImGui::Checkbox("Direction", &state.direction);
		ImGui::SliderFloat("MoveScale", &state.moveScale, 0.0f, 1000.0f, "%.2f");

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

void FloatingPlatform::Move()
{
	if (!state.direction)	// 0 : 상하
	{
		if (!check)	// Up
		{
			textureRect->Move(Vector2(0, 100));
			if (textureRect->GetPosition().y >= state.position.y + state.moveScale)
				check = true;
		}
		else		// Down
		{
			textureRect->Move(Vector2(0, -100));
			if (textureRect->GetPosition().y <= state.position.y - state.moveScale)
				check = false;
		}
	}
	else		// 1 : 좌우
	{
		if (!check)	// Right
		{
			textureRect->Move(Vector2(100, 0));
			if (textureRect->GetPosition().x >= state.position.x + state.moveScale)
				check = true;
		}
		else		// Left
		{
			textureRect->Move(Vector2(-100, 0));
			if (textureRect->GetPosition().x <= state.position.x - state.moveScale)
				check = false;
		}
	}
}
