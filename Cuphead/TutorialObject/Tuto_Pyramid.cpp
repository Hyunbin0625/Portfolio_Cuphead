#include "stdafx.h"
#include "Tuto_Pyramid.h"

Tuto_Pyramid::Tuto_Pyramid(const Vector2& position, const float& totalSize, float rotation, bool bCollision)
{
	state = { TutoType::Pyramid, position, totalSize, rotation, bCollision };

	textureRect = make_unique<TextureRect>(position, scaleR * totalSize, rotation, L"_Textures/Scene_Tutorial/tutorial_plynth_after_pyramid_is_destroyed.png");
	texturePrmid = make_unique<TextureRect>(position + Vector2(0, 255.5f) * state.totalSize, scaleP * totalSize, rotation, L"_Textures/Scene_Tutorial/tutorial_pyramid_topper.png");
	animTarget = make_unique<AnimationRect>(texturePrmid->GetPosition() + Vector2(0, 110.5f) * state.totalSize, scaleT * totalSize, rotation, L"_Textures/Scene_Tutorial/tutorial_target.png");
	animTarget->AddAnimClip(make_shared<AnimationClip>(L"Target", L"_Textures/Scene_Tutorial/tutorial_target.png", 3, false, true, 0.1));

	collisionRect = make_shared<ColorRect>(position + Vector2() * state.totalSize, colScaleR * totalSize, 0.0f, BLACK);

	textureRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
	texturePrmid->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
	animTarget->AddComponent(make_shared<ColliderComponent>(ColliderType::CIRCLE));

	collisionRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));

	animTarget->AddComponent(make_shared<AnimatorComponent>(animTarget->GetAnimClips()));
	animTarget->SetAnimator(animTarget->GET_COMP(Animator));
}

void Tuto_Pyramid::Collision(shared_ptr<Player> player)
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

	if (texturePrmid->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= PlayerState::Special_Attack_R && player->GetState() <= PlayerState::Super_Beam_L))
	{
		// 충돌시 player가 object 위인 경우
		if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 + 5 > texturePrmid->GetPosition().y + texturePrmid->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().x > texturePrmid->GetPosition().x - texturePrmid->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().x < texturePrmid->GetPosition().x + texturePrmid->GetScale().x / 2)
		{
			player->SetCheckCollider(true);
			player->SetGroundPos(Vector2(texturePrmid->GetPosition().x, texturePrmid->GetPosition().y + texturePrmid->GetScale().y / 2));

			if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < texturePrmid->GetPosition().y + texturePrmid->GetScale().y / 2 - 1)
			{
				player->GetAnimRect()->Move(Vector2(0, 400));
			}
		}

		// 충돌시 player가 object 아래인 경우
		if (player->GetAnimRect()->GetPosition().y < texturePrmid->GetPosition().y - texturePrmid->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().x > texturePrmid->GetPosition().x - texturePrmid->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().x < texturePrmid->GetPosition().x + texturePrmid->GetScale().x / 2)
		{
			player->GetAnimRect()->Move(Vector2(0, player->GetJumpSpeed()));
			player->SetJumpSpeed(0.0f);
		}

		// 충돌시 player가 object 옆인 경우
		if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < texturePrmid->GetPosition().y + texturePrmid->GetScale().y / 2
			|| player->GetAnimRect()->GetPosition().y + player->GetAnimRect()->GetScale().y / 2 < texturePrmid->GetPosition().y - texturePrmid->GetScale().y / 2)
		{
			if (player->GetAnimRect()->GetPosition().x + player->GetAnimRect()->GetScale().x / 2 > texturePrmid->GetPosition().x - texturePrmid->GetScale().x / 2
				&& player->GetAnimRect()->GetPosition().x < texturePrmid->GetPosition().x)
			{
				player->GetAnimRect()->Move(Vector2(-player->GetSpeed(), 0));
			}
			if (player->GetAnimRect()->GetPosition().x - player->GetAnimRect()->GetScale().x / 2 < texturePrmid->GetPosition().x + texturePrmid->GetScale().x / 2
				&& player->GetAnimRect()->GetPosition().x > texturePrmid->GetPosition().x)
			{
				player->GetAnimRect()->Move(Vector2(player->GetSpeed(), 0));
			}
		}
	}

	// PlayerBullts&Target
	for (int i = 0; i < player->GetBullet()->GetBullets().size(); ++i)
	{
		if (player->GetBullet()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(animTarget->GET_COMP(Collider)))
		{
			if (player->GetBullet()->GetBullets()[i]->GetHit())
			{
				player->GetBullet()->GetBullets()[i]->SetActivation(false);
				--hp;
			}
		}
	}
}

void Tuto_Pyramid::Update()
{
	if (bMod && !(ImGui::IsAnyItemActive()) && textureRect->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
		state.position = INPUT->GetMousePosition();

	textureRect->SetPosition(state.position);
	if (hp <= 0 && bActivation)
	{
		SOUND->AddSound("Burst", L"_Sounds/sfx_level_mausoluem_ghost_jar_burst_01.wav", false);
		SOUND->Play("Burst");
		bActivation = false;
		texturePrmid->SetPosition(Vector2(1000, -1000));
		animTarget->SetPosition(Vector2(1000, -1000));
	}
	else if (hp > 0)
	{
		texturePrmid->SetPosition(state.position + Vector2(-20, 172) * state.totalSize);
		animTarget->SetPosition(texturePrmid->GetPosition() + Vector2(0, 115) * state.totalSize);
	}

	collisionRect->SetPosition(state.position + Vector2(-25, -10) * state.totalSize);

	textureRect->SetScale(scaleR * state.totalSize);
	texturePrmid->SetScale(scaleP * state.totalSize);
	animTarget->SetScale(scaleT * state.totalSize);

	collisionRect->SetScale(colScaleR * state.totalSize);

	textureRect->SetRotation((float)(state.rotation * 57.2));
	collisionRect->SetRotation((float)(state.rotation * 57.2));
	texturePrmid->SetRotation((float)(state.rotation * 57.2));
	animTarget->SetRotation((float)(state.rotation * 57.2));

	textureRect->Update();
	texturePrmid->Update();
	animTarget->Update();
	collisionRect->Update();
}

void Tuto_Pyramid::Render()
{
	textureRect->Render();

	if (bActivation)
	{
		texturePrmid->Render();
		animTarget->Render();
	}

	if (bMod)
		collisionRect->Render();
}

void Tuto_Pyramid::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ". Pyramid";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		textureRect->SetOutline(true);
		texturePrmid->SetOutline(true);
		animTarget->SetOutline(true);

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
		texturePrmid->SetOutline(false);
		animTarget->SetOutline(false);
	}
}
