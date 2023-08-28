#include "stdafx.h"
#include "Barrel.h"

Barrel::Barrel()
{
	animRect = make_shared<AnimationRect>(Vector2(), Vector2(), 0.0f, L"_Textures/Pirate/pirate_barrelIdle_L.png");
	fx = make_shared<AnimationRect>(Vector2(1000, -1000), Vector2(), 0.0f, L"_Textures/Pirate/pirate_barrelFx.png");
	dust = make_shared<AnimationRect>(Vector2(1000, -1000), Vector2(), 0.0f, L"_Textures/Pirate/pirate_barrelDust.png");

	animRect->AddAnimClip(make_shared<AnimationClip>(L"IdleL", L"_Textures/Pirate/pirate_barrelIdle_L.png", 10, false, false, 0.12f));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"IdleR", L"_Textures/Pirate/pirate_barrelIdle_R.png", 10, false, false, 0.12f));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"SafeL", L"_Textures/Pirate/pirate_barrelSafe_L.png", 10, false, false, 0.12f));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"SafeR", L"_Textures/Pirate/pirate_barrelSafe_R.png", 10, false, false, 0.12f));

	animRect->AddAnimClip(make_shared<AnimationClip>(L"Drop01", L"_Textures/Pirate/pirate_barrelDrop_01.png", 2, false, true, 0.1f));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Drop02", L"_Textures/Pirate/pirate_barrelDrop_02.png", 2, false, true, 0.1f));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Drop03", L"_Textures/Pirate/pirate_barrelDrop_03.png", 2, false, true, 0.1f));

	animRect->AddAnimClip(make_shared<AnimationClip>(L"Smash", L"_Textures/Pirate/pirate_barrelSmash.png", 3, false, false, 0.1f));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"SmashL", L"_Textures/Pirate/pirate_barrelSmash_loop.png", 2, false, true, 0.1f));

	animRect->AddAnimClip(make_shared<AnimationClip>(L"Up01", L"_Textures/Pirate/pirate_barrelSmash.png", 3, true, false, 0.1f));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Up02", L"_Textures/Pirate/pirate_barrelUp.png", 6, false, false, 0.1f));

	fx->AddAnimClip(make_shared<AnimationClip>(L"Fx", L"_Textures/Pirate/pirate_barrelFx.png", 12, false, false, 0.1f));
	dust->AddAnimClip(make_shared<AnimationClip>(L"Dust", L"_Textures/Pirate/pirate_barrelDust.png", 23, false, false, 0.1f));

	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	fx->AddComponent(make_shared<AnimatorComponent>(fx->GetAnimClips()));
	dust->AddComponent(make_shared<AnimatorComponent>(dust->GetAnimClips()));

	animRect->SetAnimator(animRect->GET_COMP(Animator));
	fx->SetAnimator(fx->GET_COMP(Animator));
	dust->SetAnimator(dust->GET_COMP(Animator));

	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

Barrel::~Barrel() {}

void Barrel::Collision(shared_ptr<Player> player)
{
	if (state == BarrelState::Idle && animRect->GET_COMP(Animator)->GetEnd()
		&& player->GetAnimRect()->GetPosition().x >= animRect->GetPosition().x - animRect->GetScale().x * 0.5f
		&& player->GetAnimRect()->GetPosition().x <= animRect->GetPosition().x + animRect->GetScale().x * 0.5f)
		bDrop = true;

	if (animRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
		player->SetHit(true);

	if (player->GetIntro())
		bIntro = true;
	else
		bIntro = false;

}

void Barrel::Update()
{
	if (bMod)
		position = Vector2(840, 680);

	// Move
	if (!bIntro && (state == BarrelState::Idle || state == BarrelState::Safe))
	{
		if (moveDrctn)	// Right
		{
			position.x += speed * DELTA;
		}
		else			// Left
		{
			position.x -= speed * DELTA;
		}
	}

	if (animRect->GetPosition().x - animRect->GetScale().x * 0.5f <= minMax.x)
	{
		moveDrctn = true;
	}

	if (animRect->GetPosition().x + animRect->GetScale().x * 0.5f >= minMax.y)
		moveDrctn = false;

	if (bDrop)
		state = BarrelState::Drop;
	else if (bSmash)
		state = BarrelState::Smash;
	else if (bUp)
		state = BarrelState::Up;
	else if (bSafe)
		state = BarrelState::Safe;
	else
		state = BarrelState::Idle;

	switch (state)
	{
	case BarrelState::Idle:
		if (animDrctn)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"IdleR");
			animRect->SetScale(Vector2(210, 275) * totalSize);
			animRect->SetPosition(position);
			if (animRect->GET_COMP(Animator)->GetEnd())
				animDrctn = false;
		}
		else
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"IdleL");
			animRect->SetScale(Vector2(210, 275) * totalSize);
			animRect->SetPosition(position);
			if (animRect->GET_COMP(Animator)->GetEnd())
				animDrctn = true;
		}
		break;
	case BarrelState::Safe:
		time += DELTA;
		if (animDrctn)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"SafeR");
			animRect->SetScale(Vector2(210, 275) * totalSize);
			animRect->SetPosition(position);
			if (animRect->GET_COMP(Animator)->GetEnd())
			{
				animDrctn = false;
				if (time >= safeTime)
				{
					time = 0.0f;
					bSafe = false;
				}
			}
		}
		else
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"SafeL");
			animRect->SetScale(Vector2(210, 275) * totalSize);
			animRect->SetPosition(position);
			if (animRect->GET_COMP(Animator)->GetEnd())
			{
				animDrctn = true;
				if (time >= safeTime)
				{
					time = 0.0f;
					bSafe = false;
				}
			}
		}
		break;
	case BarrelState::Drop:
		val += G * 300.0f * DELTA;

		if (val <= 3.0f)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Drop01");
			animRect->SetScale(Vector2(165, 825) * totalSize);
			animRect->SetPosition(position + Vector2(0, 275) * totalSize);
		}
		else if (val <= 6.0f)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Drop02");
			animRect->SetScale(Vector2(165, 825) * totalSize);
			animRect->SetPosition(position + Vector2(0, 275) * totalSize);
		}
		else
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Drop03");
			animRect->SetScale(Vector2(165, 825) * totalSize);
			animRect->SetPosition(position + Vector2(0, 275) * totalSize);
		}
		position.y -= val * DELTA;
		break;
	case BarrelState::Smash:
		if (animCount == 0)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Smash");
			animRect->SetScale(Vector2(263, 834) * totalSize);
			animRect->SetPosition(position + Vector2(0, 279.5f) * totalSize);
			if (animRect->GET_COMP(Animator)->GetEnd())
			{
				++animCount;

				dust->GET_COMP(Animator)->ResetFrame();
				fx->GET_COMP(Animator)->ResetFrame();
			}
		}
		else
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"SmashL");
			animRect->SetScale(Vector2(263, 834) * totalSize);
			animRect->SetPosition(position + Vector2(0, 279.5f) * totalSize);

			fx->SetScale(Vector2(623, 380)* totalSize);
			fx->SetPosition(position + Vector2(0, -50) * totalSize);

			dust->SetScale(Vector2(477, 130)* totalSize);
			dust->SetPosition(position + Vector2(0, -80) * totalSize);

			if (fx->GET_COMP(Animator)->GetEnd())
			{
				animCount = 0;
				bSmash = false;
				bUp = true;

				fx->SetPosition(Vector2(1000, -1000));
			}
		}
		break;
	case BarrelState::Up:
		if (animCount == 0)
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Up01");
			animRect->SetScale(Vector2(263, 834) * totalSize);
			animRect->SetPosition(position + Vector2(0, 279.5f) * totalSize);

			if (animRect->GET_COMP(Animator)->GetEnd())
				++animCount;
		}
		else
		{
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Up02");
			animRect->SetScale(Vector2(165, 826) * totalSize);
			animRect->SetPosition(position + Vector2(0, 275.5) * totalSize);
			position.y += val / 2 * DELTA;

			if (position.y >= 680.0f)
			{
				position.y = 680.0f;
				animCount = 0;
				val = 0.0f;
				bUp = false;
				bSafe = true;
			}
		}

		if (dust->GET_COMP(Animator)->GetEnd())
			dust->SetPosition(Vector2(1000, -1000));
		break;
	}

	fx->Update();
	dust->Update();
	animRect->Update();
}

void Barrel::Render()
{
	animRect->Render();
	if (state == BarrelState::Smash)
	{
		fx->Render();
		dust->Render();
	}
}

void Barrel::GUI()
{
	string objName = "Barrel";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		animRect->SetOutline(true);

		ImGui::InputFloat("Pos.x", (float*)&position.x, 1.0f, 100.0f);
		ImGui::InputFloat("Pos.y", (float*)&position.y, 1.0f, 100.0f);
		ImGui::InputFloat("Speed", &speed, 1.0f, 100.0f, "%0.1f");
		ImGui::InputFloat("Scale", &totalSize, 0.1f, 10.0f, "%0.2f");
		ImGui::InputFloat("SafeTime", &safeTime);

		ImGui::EndMenu();
	}
	else
	{
		animRect->SetOutline(false);
	}
}
