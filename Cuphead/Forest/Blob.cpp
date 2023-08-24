#include "stdafx.h"
#include "Blob.h"

ForestBlob::ForestBlob(const Vector2& position, float totailSize, float speed, int maxHp, bool bRegen, float regenTime, Direction direction)
	: state({ ForestEnemyType::Blob, position, totailSize, speed, maxHp, bRegen, regenTime, direction })
{
	// ÃÊ±âÈ­
	this->hp = state.maxHp;
	direction = state.direction;
	
	animRect = make_shared<AnimationRect>(position, Vector2(135, 102) * state.totalSize, 0.0f, L"_Textures/Enemy/blob_run_R.png");

	// Move
	// Run
	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunR", L"_Textures/Enemy/blob_run_R.png", 12, true, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunL", L"_Textures/Enemy/blob_run_L.png", 12, false, true, 0.1));

	// Turn
	animRect->AddAnimClip(make_shared<AnimationClip>(L"TurnR", L"_Textures/Enemy/blob_turnaround_R.png", 7, true, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"TurnL", L"_Textures/Enemy/blob_turnaround_L.png", 7, false, false, 0.1));

	// Melt
	animRect->AddAnimClip(make_shared<AnimationClip>(L"MeltR", L"_Textures/Enemy/blob_melt_R.png", 14, true, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"MeltL", L"_Textures/Enemy/blob_melt_L.png", 14, false, false, 0.1));

	// UnMelt
	animRect->AddAnimClip(make_shared<AnimationClip>(L"UnMeltR", L"_Textures/Enemy/blob_unmelt_R.png", 19, true, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"UnMeltL", L"_Textures/Enemy/blob_unmelt_L.png", 19, false, false, 0.1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// Components
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void ForestBlob::Collision(shared_ptr<Player> player)
{
	if (animRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && animState != BlobState::Melt && animState != BlobState::UnMelt)
		player->SetHit(true);
}

void ForestBlob::Init()
{
	hp = state.maxHp;
}

void ForestBlob::Update()
{
	if (groundPos.x < -500)
		bGround = false;
	else
		bGround = true;

	if (bMod)
	{
		if (!(ImGui::IsAnyItemActive()) && animRect->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			state.position = INPUT->GetMousePosition();
		animRect->SetPosition(state.position);
		direction = state.direction;
		hp = state.maxHp;
	}

	if (bWall)
		animState = BlobState::Turn;
	else if (bGround)
	{
		animState = BlobState::Run;
		if (!bMod && hp > 0)
			Move();
	}

	if (hp <= 0)
		animState = BlobState::Melt;
	
	if (hp <= 0 && state.bRegen&& time >= state.regenTime)
	{
		animState = BlobState::UnMelt;
	}

	switch (animState)
	{
	case BlobState::Run:
		animRect->SetScale(Vector2(135, 102) * state.totalSize);
		if (bGround)
			animRect->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y + (groundPos.y - (animRect->GetPosition().y - animRect->GetScale().y / 2))));
		if (direction == Direction::R)
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunR");
		else
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunL");
		break;
	case BlobState::Turn:
		animRect->SetScale(Vector2(119, 102) * state.totalSize);
		if(direction == Direction::R)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"TurnR");
			if (animRect->GET_COMP(Animator)->GetEnd())
			{
				direction = Direction::L;
				bWall = false;
				animRect->SetPosition(Vector2(animRect->GetPosition().x - 5 * state.totalSize, animRect->GetPosition().y));
				animRect->SetScale(Vector2(135, 102) * state.totalSize);
				animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunL");
			}
		}
		else
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"TurnL");
			if (animRect->GET_COMP(Animator)->GetEnd())
			{
				direction = Direction::R;
				bWall = false;
				animRect->SetPosition(Vector2(animRect->GetPosition().x + 10 * state.totalSize, animRect->GetPosition().y));
				animRect->SetScale(Vector2(135, 102) * state.totalSize);
				animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunR");
			}
		}
		break;
	case BlobState::Melt:
		animRect->SetScale(Vector2(178, 124) * state.totalSize);
		if (direction == Direction::R)
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"MeltR");
		else
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"MeltL");
		if (animRect->GET_COMP(Animator)->GetEnd())
			time += DELTA;
		break;
	case BlobState::UnMelt:
		animRect->SetScale(Vector2(136, 116) * state.totalSize);
		if (direction == Direction::R)
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"UnMeltR");
		else
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"UnMeltL");
		if (animRect->GET_COMP(Animator)->GetEnd())
		{
			Init();
			time = 0.0f;
		}
		break;
	}

	animRect->Update();
}

void ForestBlob::Render()
{
	animRect->Render();
}

void ForestBlob::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ". Blob";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		animRect->SetOutline(true);

		ImGui::Text(objName.c_str());

		ImGui::SliderFloat2("Position", (float*)&state.position, CAMERA->GetPosition().x, CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH);
		ImGui::SliderFloat("Size", &state.totalSize, 0.1f, 5.0f, "%.2f");
		ImGui::SliderFloat("Speed", &state.speed, 100.0f, 700.0f, "%.2f");
		ImGui::InputInt("MaxHp", &state.maxHp);
		
		ImGui::Checkbox("Regen", &state.bRegen);
		ImGui::SliderFloat("RegenTime", &state.regenTime, 0.0f, 60.0f, "%.2f");
		

		bool r = 0, l = 0;
		if (state.direction)
			l = 1;
		else
			r = 1;
		ImGui::Text("Default direction");
		if (ImGui::Checkbox("L", &l))
		{
			state.direction = Direction::L;
			r = 0;
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("R", &r))
		{
			state.direction = Direction::R;
			l = 0;
		}
	
		if (ImGui::Button("Delete", ImVec2(50, 30)))
			bDelete = 1;

		ImGui::EndMenu();
	}
	else
	{
		animRect->SetOutline(false);
	}
}

void ForestBlob::Move()
{
	if (direction == Direction::R)
	{
		animRect->Move(Vector2(state.speed, 0) * state.totalSize);
	}
	else
	{
		animRect->Move(Vector2(-state.speed, 0) * state.totalSize);
	}
}
