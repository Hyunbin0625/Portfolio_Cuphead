#include "stdafx.h"
#include "SFX.h"

SFX::SFX()
{
	animRect = make_shared<AnimationRect>(Vector2(), Vector2(100, 100), 0.0f, L"_Textures/SFX/cuphead_super_intro_fx_R_50.png");
	animRect->AddAnimClip(make_shared<AnimationClip>(L"SuperIntroR", L"_Textures/SFX/cuphead_super_intro_fx_R_50.png", 11, false, false, 0.14));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"SuperIntroL", L"_Textures/SFX/cuphead_super_intro_fx_L_50.png", 11, true, false, 0.14));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"SlapSpark", L"_Textures/SFX/cuphead_slap_spark.png", 9, false, false, 0.1));
	
	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// AddComponent
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void SFX::SetAnimClip(const wstring& clipName, UINT id, Vector2 position, Vector2 scale, float rotation)
{
	this->clipName = clipName;
	this->id = id;
	activation = 1;
	if (this->id == id && this->clipName == clipName)
		animRect->GET_COMP(Animator)->ResetFrame();
	else
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(clipName);
	animRect->SetPosition(position);
	animRect->SetScale(scale);
	animRect->SetRotation(rotation);
}

void SFX::Update()
{
	if (animRect->GET_COMP(Animator)->GetEnd())
	{
		cout << "End\n";
		activation = 0;
		animRect->SetPosition(Vector2(-500, -500));
		animRect->SetScale(Vector2(100, 100));
	}
	else
	{
		animRect->Update();
		cout << "Update\n";
	}
}

void SFX::Render()
{
	animRect->Render();
}
