#include "stdafx.h"
#include "Shark.h"

Shark::Shark()
{
	animRect = make_shared<AnimationRect>(Vector2(1000, -1000), Vector2(716, 453), 0.0f, L"_Textures/Pirate/pirate_shark_fin.png");
	collisionRect = make_shared<ColorRect>(Vector2(1000, -1000), Vector2(), 0.0f, GREEN);
	dust = make_shared<AnimationRect>(Vector2(1000, -1000), Vector2(178, 156), 0.0f, L"_Textures/Pirate/pirateShark_splash.png");

	// Intro
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Intro", L"_Textures/Pirate/pirate_shark_fin.png", 3, false, true, 0.12f));

	// Entry
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Entry", L"_Textures/Pirate/pirateShark_entry.png", 8, false, false, 0.12f));

	// Bite
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Bite", L"_Textures/Pirate/pirateShark_bite.png", 10, false, false, 0.12f));

	// Leave
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Leave", L"_Textures/Pirate/pirateShark_leave.png", 8, false, true, 0.12f));

	// Dust
	dust->AddAnimClip(make_shared<AnimationClip>(L"Dust", L"_Textures/Pirate/pirateShark_splash.png", 22, false, false, 0.1f));

	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	dust->AddComponent(make_shared<AnimatorComponent>(dust->GetAnimClips()));

	animRect->SetAnimator(animRect->GET_COMP(Animator));
	dust->SetAnimator(dust->GET_COMP(Animator));

	collisionRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

Shark::~Shark() {}

void Shark::Collision(shared_ptr<Player> player)
{
	if (collisionRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
		player->SetHit(true);
}

void Shark::Init(Vector2 position, float size)
{
	state = SharkState::Intro;
	this->position = Vector2(position.x - animRect->GetScale().x * 0.5f, position.y);
	this->totalSize = size;
	animRect->SetPosition(Vector2(CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH, CENTER_Y * 0.5f + 40.0f * totalSize));
}

void Shark::Update()
{
	switch (state)
	{
	case SharkState::None:
		position = Vector2(1000, -1000);
		animRect->SetPosition(position);
		collisionRect->SetPosition(position);
		dust->SetPosition(position);
		break;
	case SharkState::Intro:
		animRect->SetScale(Vector2(178, 156) * totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Intro");
		animRect->Move(Vector2(-800.0f, 0));

		if (animRect->GetPosition().x <= CAMERA->GetPosition().x - animRect->GetScale().y)
			time += DELTA;

		if (time >= 2.0f)
		{
			state = SharkState::Entry;
			time = 0.0f;
		}
		break;
	case SharkState::Entry:
		position.x += speed * DELTA;
		animRect->SetScale(Vector2(716, 453) * totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Entry");
		animRect->SetPosition(position + Vector2(-30, 0) * totalSize);

		collisionRect->SetScale(Vector2(716, 453) * totalSize);
		collisionRect->SetPosition(position + Vector2(-30, 0) * totalSize);

		if (animRect->GET_COMP(Animator)->GetEnd())
		{
			state = SharkState::Bite;
			dust->SetPosition(position + Vector2(animRect->GetScale().x * 0.5f, position.y * 0.3f) * totalSize);
			dust->GET_COMP(Animator)->ResetFrame();
		}
		break;
	case SharkState::Bite:
		position.x += speed * DELTA;
		animRect->SetScale(Vector2(835, 535) * totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Bite");
		animRect->SetPosition(position);

		dust->SetScale(Vector2(689, 669) * totalSize);
		dust->GET_COMP(Animator)->SetCurrentAnimClip(L"Dust");
		dust->Move(Vector2(speed / 2, 0));

		collisionRect->SetScale(Vector2(835, 535) * totalSize);
		collisionRect->SetPosition(position + Vector2(-65, 0) * totalSize);

		if (animRect->GET_COMP(Animator)->GetEnd())
			state = SharkState::Leave;
		break;
	case SharkState::Leave:
		position.x -= speed * 0.5f * DELTA;
		animRect->SetScale(Vector2(795, 498) * totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Leave");
		animRect->SetPosition(position);

		collisionRect->SetScale(Vector2(795, 498) * totalSize);
		collisionRect->SetPosition(position + Vector2(-60, 0) * totalSize);

		if (position.x <= CAMERA->GetPosition().x - animRect->GetScale().x)
			state = SharkState::None;
		break;
	}

	if (state == SharkState::Leave || state == SharkState::Bite)
	{
		if (dust->GET_COMP(Animator)->GetEnd())
			dust->SetPosition(Vector2(1000, -1000));
	}

	dust->Update();
	collisionRect->Update();
	animRect->Update();
}

void Shark::ItRender()
{
	if (state == SharkState::Intro)
		animRect->Render();
}

void Shark::Render()
{
	if (state != SharkState::Intro && state != SharkState::None)
	{
	//	collisionRect->Render();
		animRect->Render();
		dust->Render();
	}
}

void Shark::GUI()
{
	string objName = "Shark";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		animRect->SetOutline(true);

		if (ImGui::InputFloat("Pos.x", (float*)&position.x, 1.0f, 100.0f))
			animRect->SetPosition(position);
		if (ImGui::InputFloat("Pos.y", (float*)&position.y, 1.0f, 100.0f))
			animRect->SetPosition(position);
		
		ImGui::InputFloat("Speed", &speed, 1.0f, 100.0f, "%0.1f");
		ImGui::InputFloat("Scale", &totalSize, 0.1f, 10.0f, "%0.2f");

		ImGui::EndMenu();
	}
	else
	{
		animRect->SetOutline(false);
	}
}
