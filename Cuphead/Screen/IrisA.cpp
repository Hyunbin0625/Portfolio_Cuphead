#include "stdafx.h"
#include "IrisA.h"

IrisA::IrisA()
{
	animRect = make_unique<AnimationRect>(CAMERA->GetPosition() + CENTER, Vector2(1280, 720), 0.0f, L"_Textures/ScreenFx/irisA.png");

	animRect->AddAnimClip(make_shared<AnimationClip>(L"Start", L"_Textures/ScreenFx/irisA.png", 17, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"End", L"_Textures/ScreenFx/irisA.png", 17, true, false, 0.1));

	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	animRect->SetAnimator(animRect->GET_COMP(Animator));
}

IrisA::~IrisA() {}

void IrisA::Start()
{
	bAnimEnd = false;
	animRect->GET_COMP(Animator)->ResetFrame();
	animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Start");
}

void IrisA::End()
{
	bAnimEnd = false;
	animRect->GET_COMP(Animator)->ResetFrame();
	animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"End");
}

void IrisA::Update()
{
	if (animRect->GET_COMP(Animator)->GetEnd())
		bAnimEnd = true;

	animRect->SetPosition(CAMERA->GetPosition() + CENTER);
	animRect->Update();
}

void IrisA::Render()
{
	animRect->Render();
}
