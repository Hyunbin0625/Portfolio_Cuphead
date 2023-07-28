#include "stdafx.h"
#include "UI.h"

Ui::Ui()
{
	// Hp
	hp = make_unique<AnimationRect>(Vector2(), Vector2(78, 32), 0.0f, L"_Textures/UI/hud_hp_3.png");
	hp->AddAnimClip(make_shared<AnimationClip>(L"HP3", L"_Textures/UI/hud_hp_3.png", 1, false, false, 1));
	hp->AddAnimClip(make_shared<AnimationClip>(L"HP2", L"_Textures/UI/hud_hp_2.png", 1, false, false, 1));
	hp->AddAnimClip(make_shared<AnimationClip>(L"HP1", L"_Textures/UI/hud_hp_1.png", 1, false, false, 1));
	hp->AddAnimClip(make_shared<AnimationClip>(L"AnimHP1", L"_Textures/UI/hud_hp_1_flash.png", 2, false, true, 0.1));
	hp->AddAnimClip(make_shared<AnimationClip>(L"Dead", L"_Textures/UI/hud_hp_dead.png", 1, false, false, 1));
	// AddAnimator
	hp->AddComponent(make_shared<AnimatorComponent>(hp->GetAnimClips()));
	// animRect SetAnimator
	hp->SetAnimator(hp->GET_COMP(Animator));

	// SuperMeterCard
	superMeterCards.assign(5, make_shared<SuperMeterCard>());

	for (auto& superMeterCard : superMeterCards)
		superMeterCard = make_shared<SuperMeterCard>();
}

Ui::~Ui()
{
}

void Ui::Init(Vector2 position, UINT currentHp, int cardPoint)
{
	hp->SetPosition(Vector2(position.x + 48, position.y + 22));
	switch (currentHp)
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

	for (int i = 0; i < superMeterCards.size(); ++i)
	{
		superMeterCards[i]->SetPosition(Vector2(position.x + i * 25, position.y));
		superMeterCards[i]->SetActivation(false);
	//	cout << "superMeterCards" << i << " : " <<  superMeterCards[i]->GetPosition().x << ", " << superMeterCards[i]->GetPosition().y << '\n';
	}
	switch (cardPoint)
	{
	case 100:
		superMeterCards[4]->SetActivation(true);
	case 90:
	case 80:
		superMeterCards[3]->SetActivation(true);
	case 70:
	case 60:
		superMeterCards[2]->SetActivation(true);
	case 50:
	case 40:
		superMeterCards[1]->SetActivation(true);
	case 30:
	case 20:
		superMeterCards[0]->SetActivation(true);
	}
}

void Ui::Update()
{
	hp->Update();
	
	for (auto& superMeterCard : superMeterCards)
		superMeterCard->Update();
}

void Ui::Render()
{
	hp->Render();
	for (auto& superMeterCard : superMeterCards)
	{
		if (superMeterCard->GetActivation())
			superMeterCard->Render();
	}
}
