#include "stdafx.h"
#include "SuperMeterCard.h"

SuperMeterCard::SuperMeterCard()
{
	animRect = make_unique<AnimationRect>(Vector2(108, 62), Vector2(20, 30), 0.0f, L"_Textures/UI/hud_mm_card_flip.png");
	animRect->AddAnimClip(make_shared<AnimationClip>(L"AnimCardMax", L"_Textures/UI/hud_mm_card_flip.png", 6, false, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"CardFlip", L"_Textures/UI/hud_ch_card_flip_0001.png", 1, false, false, 1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"CardMax", L"_Textures/UI/hud_ch_card_flip_0006.png", 1, false, false, 1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

//	animRect->SetShader();
}

void SuperMeterCard::Update()
{
	animRect->SetPosition(Vector2(position.x + 107, position.y + 22));
	animRect->Update();
}

void SuperMeterCard::Render()
{
	animRect->Render();
}
