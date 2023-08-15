#include "stdafx.h"
#include "Sphere.h"

Sphere::Sphere(Vector2 position, Vector2 Scale, float rotation, bool parrySlap)
	: position(position), rotation(rotation), bParrySlap(parrySlap)
{
	animRect = make_unique<AnimationRect>(position, Scale, rotation, L"_Textures/Scene_Tutorial/tutorial_sphere.png");
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Sphere", L"_Textures/Scene_Tutorial/tutorial_sphere.png", 2, false, true, 1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"PinkSphere", L"_Textures/Scene_Tutorial/tutorial_pink_sphere.png", 2, false, true, 1));
	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::CIRCLE));
}

void Sphere::CheckCollision(shared_ptr<Player> player)
{
	if (!bParrySlap) return;

	if (animRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
	{
		if (player->GetParry())
		{
			player->SetJumpSpeed(400.0f);
			player->SetVel(0.0f);
			player->SetSuperMeterCard((float)(player->GetSuperMeterCard() + 0.2 * player->GetMaxSuperMeterCard()));	// 20 퍼센트 추가
			bParrySlap = 0;
		}
		else if (bObstacle)	// 충돌 object인 경우
			player->SetHit(true);
	}
}

void Sphere::Update()
{
	animRect->SetPosition(position);
	animRect->SetRotation(rotation);

	if (bParrySlap)
	{
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"PinkSphere");
		animRect->SetScale(Vector2(73, 71) * size);
	}
	else
	{
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Sphere");
		animRect->SetScale(Vector2(48, 48) * size);
	}

	animRect->Update();
}

void Sphere::Render()
{
	animRect->Render();
}

void Sphere::GUI()
{
	static bool bOpen = true;
	if (ImGui::Begin("Shpere", &bOpen))
	{
		ImGui::SliderFloat2("Position", (float*)&position, 0, gWinWidth, "%.2f");
		ImGui::SliderFloat("Size", &size, 0, 2, "%.2f");
		ImGui::SliderAngle("Rotation", &rotation);
		
		ImGui::Checkbox("ParrySlap", &bParrySlap);
		ImGui::Checkbox("obstacle", &bObstacle);
	}
	ImGui::End();
}
