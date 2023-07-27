#include "stdafx.h"
#include "Scene_Test.h"

void Scene::Init()
{
	player = make_shared<Player>(CENTER, Vector2(101, 159), 300.0f, 3, 100.0f);
	ground = make_unique<ColorRect>(Vector2(CENTER_X, 100), Vector2(WIN_DEFAULT_WIDTH, 3), 0.0f, BLACK);
	ground2 = make_unique<ColorRect>(Vector2(CENTER_X, 300), Vector2(300, 3), 0.0f, BLACK);

	hp = make_unique<AnimationRect>(Vector2(48, 22), Vector2(78, 32), 0.0f, L"_Textures/Scene/hud_hp_3.png");
	hp->AddAnimClip(make_shared<AnimationClip>(L"HP3", L"_Textures/Scene/hud_hp_3.png", 1, false, false, 1));
	hp->AddAnimClip(make_shared<AnimationClip>(L"HP2", L"_Textures/Scene/hud_hp_2.png", 1, false, false, 1));
	hp->AddAnimClip(make_shared<AnimationClip>(L"HP1", L"_Textures/Scene/hud_hp_1.png", 1, false, false, 1));
	hp->AddAnimClip(make_shared<AnimationClip>(L"AnimHP1", L"_Textures/Scene/hud_hp_1_flash.png", 2, false, true, 0.1));
	hp->AddAnimClip(make_shared<AnimationClip>(L"Dead", L"_Textures/Scene/hud_hp_dead.png", 1, false, false, 1));
	// AddAnimator
	hp->AddComponent(make_shared<AnimatorComponent>(hp->GetAnimClips()));
	// animRect SetAnimator
	hp->SetAnimator(hp->GET_COMP(Animator));

	superMeterCards.assign(5, shared_ptr<AnimationRect>());
	for (auto& superMeterCard : superMeterCards)
	{
		superMeterCard = make_unique<AnimationRect>(Vector2(108, 62), Vector2(20, 30), 0.0f, L"_Textures/Scene/hud_mm_card_flip.png");
		superMeterCard->AddAnimClip(make_shared<AnimationClip>(L"AnimCardMax", L"_Textures/Scene/hud_mm_card_flip.png", 6, false, true, 0.1));
		superMeterCard->AddAnimClip(make_shared<AnimationClip>(L"CardFlip", L"_Textures/Scene/hud_ch_card_flip_0001.png", 1, false, false, 1));
		superMeterCard->AddAnimClip(make_shared<AnimationClip>(L"CardMax", L"_Textures/Scene/hud_ch_card_flip_0006.png", 1, false, false, 1));
		// AddAnimator
		superMeterCard->AddComponent(make_shared<AnimatorComponent>(superMeterCard->GetAnimClips()));
		// animRect SetAnimator
		superMeterCard->SetAnimator(superMeterCard->GET_COMP(Animator));
	}

	for (auto& superMeterCard : superMeterCards)
		superMeterCard->GET_COMP(Animator)->SetCurrentAnimClip(L"AnimCardMax");

	sphere = make_unique<Sphere>(Vector2(1100, 300), Vector2(48, 48), 0.0f, true);

	// AddComponent
	ground->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
	ground2->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void Scene::Destroy()
{
}

void Scene::Update()
{	
	CheckGround();

	player->Update();

	ground->Update();
	ground2->Update();

	sphere->Update();

	sphere->CheckCollision(player);

	for (int i = 0; i < superMeterCards.size(); ++i)
	{
		superMeterCards[i]->SetPosition(Vector2(-100, -100));
	}
	switch (player->GetPercentSuperMeterCard())
	{
	case 20:
	case 30:
		for (int i = 0; i < superMeterCards.size() - 4; ++i)
			superMeterCards[i]->SetPosition(Vector2(107 + i * 25, 22));
		break;
	case 40:
	case 50:
		for (int i = 0; i < superMeterCards.size() - 3; ++i)
			superMeterCards[i]->SetPosition(Vector2(107 + i * 25, 22));
		break;
	case 60:
	case 70:
		for (int i = 0; i < superMeterCards.size() - 2; ++i)
			superMeterCards[i]->SetPosition(Vector2(107 + i * 25, 22));
		break;
	case 80:
	case 90:
		for (int i = 0; i < superMeterCards.size() - 1; ++i)
			superMeterCards[i]->SetPosition(Vector2(107 + i * 25, 22));
		break;
	case 100:
		for (int i = 0; i < superMeterCards.size(); ++i)
			superMeterCards[i]->SetPosition(Vector2(107 + i * 25, 22));
		break;
	}

	for (auto& superMeterCard : superMeterCards)
		superMeterCard->Update();

	switch (player->GetHp())
	{
	case 0:
		hp->GET_COMP(Animator)->SetCurrentAnimClip(L"Dead");
		break;
	case 1:
		hp->GET_COMP(Animator)->SetCurrentAnimClip(L"HP1");
		break;
	case 2:
		hp->GET_COMP(Animator)->SetCurrentAnimClip(L"HP2");
		break;
	case 3:
		hp->GET_COMP(Animator)->SetCurrentAnimClip(L"HP3");
		break;
	}
	hp->Update();
}

void Scene::PreRender()
{
}

void Scene::Render()
{
	ground->Render();
	ground2->Render();
	sphere->Render();
	player->Render();

	for (auto& superMeterCard : superMeterCards)
		superMeterCard->Render();
	hp->Render();
}

void Scene::PostRender()
{
	player->GUI();
	sphere->GUI();
}

// 각 플렛폼에서 검사할 예정
void Scene::CheckGround()
{
	player->SetCheckCollider(0);
	player->SetPlatform(0);
	if (ground->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= State::Special_Attack_R && player->GetState() <= State::Super_Beam_L))
	{
		player->SetGroundPos(Vector2(ground->GetPosition().x, ground->GetPosition().y + ground->GetScale().y / 2));
		player->SetCheckCollider(1);
		if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < ground->GetPosition().y + ground->GetScale().y / 2 - 1)
			player->GetAnimRect()->Move(Vector2(0, 400));
	}

	if (ground2->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= State::Special_Attack_R && player->GetState() <= State::Super_Beam_L))
	{
		player->SetGroundPos(Vector2(ground2->GetPosition().x, ground2->GetPosition().y + ground2->GetScale().y / 2));
		player->SetCheckCollider(1);
		player->SetPlatform(1);
		if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < ground2->GetPosition().y + ground2->GetScale().y / 2 - 1)
			player->GetAnimRect()->Move(Vector2(0, 400));
	}
}
