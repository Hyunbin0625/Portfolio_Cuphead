#include "stdafx.h"
#include "CroaksFirefly.h"

CroaksFirefly::CroaksFirefly(float speed)
	: speed(speed)
{
	// √ ±‚»≠
	animRect = make_shared<AnimationRect>(Vector2(1000, -1000), Vector2(119, 197), 0.0f, L"_Textures/RibbyCroaks/tallfrog_firefly_idle.png");

	// Move
	// Idle
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Idle", L"_Textures/RibbyCroaks/tallfrog_firefly_idle.png", 10, false, true, 0.09));
	// Left
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Left", L"_Textures/RibbyCroaks/tallfrog_firefly_left.png", 4, false, true, 0.09));
	// Right
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Right", L"_Textures/RibbyCroaks/tallfrog_firefly_right.png", 4, true, true, 0.09));
	// Up
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Up", L"_Textures/RibbyCroaks/tallfrog_firefly_up.png", 4, false, true, 0.09));
	// Down
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Down", L"_Textures/RibbyCroaks/tallfrog_firefly_down.png", 4, false, true, 0.09));
	// Death
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Death", L"_Textures/RibbyCroaks/tallfrog_firefly_death.png", 9, false, false, 0.1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// Components
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void CroaksFirefly::Collision(shared_ptr<Player> player)
{
	if (animRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && animState != CroaksFireflyState::Death)
	{
		hp = 0;
		player->SetHit(true);
	}

	playerPos = player->GetAnimRect()->GetPosition();

	// playerBullts&enemies Collision
	for (int i = 0; i < player->GetBullet()->GetBullets().size(); ++i)
	{
		if (player->GetBullet()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(animRect->GET_COMP(Collider)) && animState != CroaksFireflyState::Death)
		{
			--hp;
			player->GetBullet()->GetBullets()[i]->SetActivation(false);
		}
	}

	for (int i = 0; i < player->GetSpecialAttack()->GetBullets().size(); ++i)
	{
		if (player->GetSpecialAttack()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(animRect->GET_COMP(Collider)))
			--hp;
	}

	if (player->GetSuperBeam()->GetAnimRect()->GET_COMP(Collider)->Intersect(animRect->GET_COMP(Collider)))
		--hp;
}

void CroaksFirefly::Init(Vector2 position, Vector2 startPos)
{
	bActivation = true;
	hp = 1;
	time = 0.0f;
	bMove = true;
	this->startPos = startPos;
	animRect->SetPosition(position);
	animState = CroaksFireflyState::Idle;
}

void CroaksFirefly::Update()
{
	time += DELTA;

	if (startPos.x != 0.0f)
	{
		dist = Vector2(startPos.x - animRect->GetPosition().x, startPos.y - animRect->GetPosition().y);
		if(dist.x >= 0.0f)
			dist = Vector2();
		else
			dist.Normalize();
	}

	if ((startPos.x != 0.0f && time >= 1.5f && bMove)
		|| (startPos.x == 0.0f && time >= 0.4f && bMove))
	{
		startPos = Vector2();
		dist = Vector2();
		time = 0.0f;
		bMove = false;
	}
	
	if (time >= 2.0f && !bMove)
	{
		time = 0.0f;
		bMove = true;

		if (startPos.x == 0.0f)
		{
			dist = Vector2(playerPos.x - animRect->GetPosition().x, playerPos.y - animRect->GetPosition().y);
			if (dist.x < 15.0f && dist.x > -15.0f)
				dist.x = 0.0f;
			dist.Normalize();
		}
	}

	if (bMove)
		animRect->Move(dist * speed);

	animState = CroaksFireflyState::Idle;
	if(dist.x > 0.0f)
		animState = CroaksFireflyState::Right;
	if(dist.x < 0.0f)
		animState = CroaksFireflyState::Left;
	if (dist.x == 0.0f && dist.y > 0.0f)
		animState = CroaksFireflyState::Up;
	if (dist.x == 0.0f && dist.y < 0.0f)
		animState = CroaksFireflyState::Down;
	if (hp <= 0)
		animState = CroaksFireflyState::Death;

	switch (animState)
	{
	case CroaksFireflyState::Idle:
		animRect->SetScale(Vector2(119, 197) * (float)(1 * totalSize));
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Idle");
		break;
	case CroaksFireflyState::Left:
		animRect->SetScale(Vector2(136, 192) * (float)(1 * totalSize));
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Left");
		break;
	case CroaksFireflyState::Right:
		animRect->SetScale(Vector2(136, 192) * (float)(1 * totalSize));
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Right");
		break;
	case CroaksFireflyState::Up:
		animRect->SetScale(Vector2(117, 224) * (float)(1 * totalSize));
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Up");
		break;
	case CroaksFireflyState::Down:
		animRect->SetScale(Vector2(121, 203) * (float)(1 * totalSize));
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Down");
		break;
	case CroaksFireflyState::Death:
		animRect->SetScale(Vector2(608, 611) * (float)(1 * totalSize));
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Death");
		if (animRect->GET_COMP(Animator)->GetEnd())
		{
			bActivation = false;
			animRect->SetPosition(Vector2(1000, -1000));
		}
		break;
	}

	animRect->Update();
}

void CroaksFirefly::Render()
{
	animRect->Render();
}
