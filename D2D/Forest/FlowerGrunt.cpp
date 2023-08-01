#include "stdafx.h"
#include "FlowerGrunt.h"

FlowerGrunt::FlowerGrunt(const Vector2& position, float totailSize, float speed, int maxHp, bool bRegen, float regenTime, Direction direction)
	: state({ ForestEnemyType::FlowerGrunt, position, totailSize, speed, maxHp, bRegen, regenTime, direction })
{
	// ÃÊ±âÈ­
	this->hp = state.maxHp;
	direction = state.direction;
	
	animRect = make_shared<AnimationRect>(position, Vector2(207, 248) * state.totalSize, 0.0f, L"_Textures/Enemy/flowergrunt_float_R.png");

	// Move
	// Float
	animRect->AddAnimClip(make_shared<AnimationClip>(L"FloatR", L"_Textures/Enemy/flowergrunt_float_R.png", 28, true, true, 0.09));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"FloatL", L"_Textures/Enemy/flowergrunt_float_L.png", 28, false, true, 0.09));
	// Run
	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunR", L"_Textures/Enemy/flowergrunt_run_R.png", 16, true, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunL", L"_Textures/Enemy/flowergrunt_run_L.png", 16, false, true, 0.1));

	// Jump

	// Turn
	animRect->AddAnimClip(make_shared<AnimationClip>(L"TurnR", L"_Textures/Enemy/flowergrunt_turn_R.png", 18, true, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"TurnL", L"_Textures/Enemy/flowergrunt_turn_L.png", 18, false, false, 0.1));
	
	// Death
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Death", L"_Textures/Enemy/generic_lg_explosion_a_star_b_40.png", 20, false, false, 0.1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// Components
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));

}

void FlowerGrunt::Collision(shared_ptr<Player> player)
{
	if (animRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && AnimState != FwGruntState::Death)
		player->SetHit(true);
}

void FlowerGrunt::Init()
{
	animRect->SetPosition(state.position);
	hp = state.maxHp;
	direction = state.direction;
	groundPos = Vector2(-1000, -1000);
}

void FlowerGrunt::Update()
{
	if (hp <= 0 && state.bRegen && time < state.regenTime)
	{
		time += DELTA;
	}
	else if ( hp <= 0 && !(state.position.x > CAMERA->GetPosition().x - 100 && state.position.x < CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH + 100
		&& state.position.y > CAMERA->GetPosition().y - 100 && state.position.y < CAMERA->GetPosition().y + WIN_DEFAULT_HEIGHT + 100))
	{
		Init();
		time = 0;
	}

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

//	cout << hp << '\n';
	if (bWall)
		AnimState = FwGruntState::Turn;
	else if (bGround)
	{
		AnimState = FwGruntState::Run;
		if (!bMod && hp > 0)
			Move();
	}
	else
	{
		// Float
		if (!bMod && hp > 0)
			animRect->Move(Vector2(0, -100));
		AnimState = FwGruntState::Float;
	}



	if (hp <= 0)
		AnimState = FwGruntState::Death;

	switch (AnimState)
	{
	case FwGruntState::Run:
		animRect->SetScale(Vector2(179, 193) * state.totalSize);
		animRect->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y + (groundPos.y - (animRect->GetPosition().y - animRect->GetScale().y / 2))));
		if (direction == Direction::R)
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunR");
		else
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunL");
		break;
	case FwGruntState::Float:
		animRect->SetScale(Vector2(207, 248) * state.totalSize);
		if (direction == Direction::R)
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"FloatR");
		else
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"FloatL");
		break;
	case FwGruntState::Jump:
		break;
	case FwGruntState::Turn:
		animRect->SetScale(Vector2(315, 218) * state.totalSize);
	if(direction == Direction::R)
	{
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"TurnR");
		if (animRect->GET_COMP(Animator)->GetEnd())
		{
			direction = Direction::L;
			bWall = false;
			animRect->SetPosition(Vector2(animRect->GetPosition().x - 5 * state.totalSize, animRect->GetPosition().y));
			animRect->SetScale(Vector2(179, 193) * state.totalSize);
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
			animRect->SetScale(Vector2(179, 193) * state.totalSize);
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"RunR");
		}
	}
		break;
	case FwGruntState::Death:
		animRect->SetScale(Vector2(234, 261) * 1.5 * state.totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Death");
		if (animRect->GET_COMP(Animator)->GetEnd())
			animRect->SetPosition(Vector2(1000, -1000));
		break;
	}

	animRect->Update();
}

void FlowerGrunt::Render()
{
	animRect->Render();
}

void FlowerGrunt::GUI(int ordinal)
{
	string objName = animRect->GetName() + to_string(ordinal);

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

void FlowerGrunt::Move()
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
