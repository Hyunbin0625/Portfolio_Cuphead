#include "stdafx.h"
#include "Acorn.h"

Acorn::Acorn(const Vector2& position, float totalSize, float speed, int maxHp, bool bRegen, float regenTime, Direction direction)
	: state({ ForestEnemyType::Acorn, position, totalSize, speed, maxHp, bRegen, regenTime, direction })
{
	// 초기화
	this->hp = state.maxHp;
	direction = state.direction;
	animState = AcornState::Drop;
	
	animRect = make_shared<AnimationRect>(Vector2(position), Vector2(142, 157) * state.totalSize, 0.0f, L"_Textures/Enemy/flowergrunt_float_R.png");

	// Move
	// Fly
	animRect->AddAnimClip(make_shared<AnimationClip>(L"FlyR", L"_Textures/Enemy/acorn_fly_R.png", 20, true, true, 0.09));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"FlyL", L"_Textures/Enemy/acorn_fly_L.png", 20, false, true, 0.09));

	// Drop
	animRect->AddAnimClip(make_shared<AnimationClip>(L"DropR", L"_Textures/Enemy/acorn_drop_R.png", 3, true, false, 0.09));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"DropL", L"_Textures/Enemy/acorn_drop_L.png", 3, false, false, 0.09));

	// DropLoop
	animRect->AddAnimClip(make_shared<AnimationClip>(L"DropLoop", L"_Textures/Enemy/acorn_drop_loop.png", 14, false, true, 0.09));

	// Death
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Death", L"_Textures/Enemy/generic_lg_explosion_a_star_b_40.png", 20, false, false, 0.1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// Components
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));


	// Prop
	subAnimRect = make_shared<AnimationRect>(Vector2(1000, -1000), Vector2(142, 37) * state.totalSize, 0.0f, L"_Textures/Enemy/acorn_prop.png");

	subAnimRect->AddAnimClip(make_shared<AnimationClip>(L"Prop", L"_Textures/Enemy/acorn_prop.png", 6, false, true, 0.1));

	// AddAnimator
	subAnimRect->AddComponent(make_shared<AnimatorComponent>(subAnimRect->GetAnimClips()));
	// animRect SetAnimator
	subAnimRect->SetAnimator(subAnimRect->GET_COMP(Animator));
}

void Acorn::Collision(shared_ptr<Player> player)
{
	if (animRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && animState != AcornState::Death)
		player->SetHit(true);

	playerX = player->GetAnimRect()->GetPosition().x;
}

void Acorn::Init()
{
	time = 0.0f;
	animRect->SetPosition(state.position);
	hp = state.maxHp;
	direction = state.direction;
	animState = AcornState::Fly;
}

void Acorn::Update()
{
	// 범위 활성화
	if (direction == Direction::R)
	{
		if (state.position.x < CAMERA->GetPosition().x - 100 && state.position.x > CAMERA->GetPosition().x - (WIN_DEFAULT_WIDTH + 100))
			bActivation = true;
		else
			bActivation = false;
	}
	else
	{
		if (state.position.x > CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH + 100 && state.position.x < CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH * 2 + 100)
			bActivation = true;
		else
			bActivation = false;
	}

	if (hp <= 0 && state.bRegen && time < state.regenTime)
	{
		time += DELTA;
	}
	else if (hp <= 0 && !(state.position.x > CAMERA->GetPosition().x - 100 && state.position.x < CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH + 100
		&& state.position.y > CAMERA->GetPosition().y - 100 && state.position.y < CAMERA->GetPosition().y + WIN_DEFAULT_HEIGHT + 100))
	{
		if (bActivation)
			Init();
	}

	if (bMod)
	{
		if (!(ImGui::IsAnyItemActive()) && animRect->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			state.position = INPUT->GetMousePosition();
		animRect->SetPosition(state.position);
		direction = state.direction;
		hp = state.maxHp;
		bActivation = true;
		animState = AcornState::Drop;
	}

	if (hp <= 0)
	{
		subAnimRect->SetPosition(Vector2(1000, -1000));
		animState = AcornState::Death;
	}

	switch (animState)
	{
	case AcornState::Fly:
		animRect->SetScale(Vector2(142, 157) * state.totalSize);
		if (!bMachine)
			animRect->SetPosition(Vector2(animRect->GetPosition().x, CAMERA->GetPosition().y + WIN_DEFAULT_HEIGHT - 100));
		if (direction == Direction::R)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"FlyR");
			if (!bMachine)
				animRect->Move(Vector2(state.speed, 0));
			if (animRect->GetPosition().x >= playerX)
				animState = AcornState::Drop;
		}
		else
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"FlyL");
			if (!bMachine)
				animRect->Move(Vector2(-state.speed, 0));
			if (animRect->GetPosition().x <= playerX)
				animState = AcornState::Drop;
		}
		break;
	case AcornState::Drop:
		subAnimRect->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y + animRect->GetScale().y / 2));
		animRect->SetScale(Vector2(113, 150) * state.totalSize);
		if (direction == Direction::R)
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"DropR");
		else
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"DropL");
		if (animRect->GET_COMP(Animator)->GetEnd())
			animState = AcornState::DropLoop;
		break;
	case AcornState::DropLoop:
		animRect->SetScale(Vector2(113, 150) * state.totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"DropLoop");
		animRect->Move(Vector2(0, -600));
		subAnimRect->Move(Vector2(0, 700));
		if (animRect->GetPosition().y <= CAMERA->GetPosition().y - WIN_DEFAULT_HEIGHT + 100)
		{
			bActivation = false;
			hp = 0;
		}
		break;
	case AcornState::Death:
		animRect->SetScale(Vector2(234, 261) * 0.9 * state.totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Death");
		if (animRect->GET_COMP(Animator)->GetEnd())
			animRect->SetPosition(Vector2(1000, -1000));
		break;
	}

	subAnimRect->Update();
	animRect->Update();
}

void Acorn::Render()
{
	animRect->Render();
	subAnimRect->Render();
}

void Acorn::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ". Acorn";

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
