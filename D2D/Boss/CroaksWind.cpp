#include "stdafx.h"
#include "CroaksWind.h"

CroaksWind::CroaksWind(float maxSpeed)
	: maxSpeed(maxSpeed)
{
	// √ ±‚»≠
	animRect = make_shared<AnimationRect>(Vector2(1000, -1000), Vector2(669, 568), 0.0f, L"_Textures/RibbyCroaks/tallfrog_fan_wind_intro.png");

	// Intro
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Intro", L"_Textures/RibbyCroaks/tallfrog_fan_wind_intro.png", 4, false, false, 0.15));
	// Loop
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Loop", L"_Textures/RibbyCroaks/tallfrog_fan_wind_loop.png", 5, false, true, 0.15));
	// End
	animRect->AddAnimClip(make_shared<AnimationClip>(L"End", L"_Textures/RibbyCroaks/tallfrog_fan_wind_intro.png", 4, true, false, 0.15));
	
	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// Components
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void CroaksWind::Collision(shared_ptr<Player> player)
{
	if (animRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
		player->GetAnimRect()->Move(Vector2(-1, 0) * speed);
}

void CroaksWind::Init(Vector2 position, float totalSize)
{
	bActivation = true;
	++count;
	this->totalSize = totalSize;
	this->position = position;
}

void CroaksWind::Update()
{
	if (bActivation)
	{
		animRect->SetScale(Vector2(669, 568) * totalSize);
		animRect->SetPosition(position);
		if (count == 1)
		{
			if (speed <= maxSpeed)
				speed += maxSpeed / 4;
			if (speed > maxSpeed)
				speed = maxSpeed;
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Intro");
		}
		else if (count == 2)
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Loop");
		else
		{
			if (speed >= 0)
				speed -= maxSpeed / 4;
			if (speed < 0)
				speed = 0;
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"End");
			if (animRect->GET_COMP(Animator)->GetEnd())
			{
				bActivation = false;
				count = 0;
			}
		}
	}
	else
		animRect->SetPosition(Vector2(1000, -1000));

	animRect->Update();
}

void CroaksWind::Render()
{
	if (bActivation)
		animRect->Render();
}
