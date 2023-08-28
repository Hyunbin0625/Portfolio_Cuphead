#include "stdafx.h"
#include "PirateBeam.h"

PirateBeam::PirateBeam()
{
	animRect = make_shared<AnimationRect>(Vector2(), Vector2(968, 185), 0.0f, L"_Textures/Pirate/pirate_beam_start.png");
	collisionRect = make_shared<ColorRect>(Vector2(), Vector2(), 0.0f, GREEN);

	// Intro
	animRect->AddAnimClip(make_shared<AnimationClip>(L"BeamS", L"_Textures/Pirate/pirate_beam_start.png", 3, false, false, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"BeamL", L"_Textures/Pirate/pirate_beam_loop.png", 4, true, true, 0.1));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"BeamE", L"_Textures/Pirate/pirate_beam_start.png", 3, true, false, 0.1));
	
	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// AddComponent
	collisionRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

PirateBeam::~PirateBeam() {}

void PirateBeam::Init(Vector2 position, float totalSize)
{
	this->totalSize = totalSize;

	bPirateBeam = true;
	bEnd = false;
	count = 0;
	animRect->SetScale(Vector2(968, 185) * totalSize);
	animRect->SetPosition(position + Vector2(-animRect->GetScale().x * 0.5f + 110, -33) * totalSize);

	animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"BeamS");
	animRect->GET_COMP(Animator)->ResetFrame();
}

void PirateBeam::Update()
{
	if (bPirateBeam)
	{
		if (count == 0)
		{
			collisionRect->SetPosition(animRect->GetPosition());
			collisionRect->SetScale(Vector2(968, 75) * totalSize);

			if (animRect->GET_COMP(Animator)->GetEnd())
				++count;
		}
		else if (bEnd)
		{
			collisionRect->SetPosition(animRect->GetPosition());
			collisionRect->SetScale(Vector2(968, 75) * totalSize);

			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"BeamE");
			if (animRect->GET_COMP(Animator)->GetEnd())
				bPirateBeam = false;
		}
		else
		{
			collisionRect->SetPosition(animRect->GetPosition());
			collisionRect->SetScale(Vector2(968, 105) * totalSize);

			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"BeamL");
		}
	}

	if (bPirateBeam == false)
	{
		animRect->SetPosition(Vector2(-1000, -1000));
		collisionRect->SetPosition(Vector2(-1000, -1000));
	}

	animRect->Update();
	collisionRect->Update();
}

void PirateBeam::Render()
{
	if (bPirateBeam)
	{
	//	collisionRect->Render();
		animRect->Render();
	}
}
