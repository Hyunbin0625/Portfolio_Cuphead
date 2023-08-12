#include "stdafx.h"
#include "RibbyCroaks.h"

RibbyCroaks::RibbyCroaks(RibbyCroaksInfo ribbyInfo, RibbyCroaksInfo croaksInfo, UINT maxHp, float delay)
	: ribbyInfo(ribbyInfo), croaksInfo(croaksInfo), maxHp(maxHp), delay(delay)
{
	// 초기화
	hp = 510;
	random_device random;
	mt = mt19937(random());

	// Ribby
	ribby = make_shared<AnimationRect>(ribbyInfo.position, Vector2(370, 350) * ribbyInfo.totalSize, 0.0f, L"_Textures/RibbyCroaks/shortFrog_idle_L.png");

	// Moves
	// Idle
	ribby->AddAnimClip(make_shared<AnimationClip>(L"IdleR", L"_Textures/RibbyCroaks/shortFrog_idle_R.png", 36, true, true, 0.1));
	ribby->AddAnimClip(make_shared<AnimationClip>(L"IdleL", L"_Textures/RibbyCroaks/shortFrog_idle_L.png", 36, false, true, 0.1));

	// Intro
	ribby->AddAnimClip(make_shared<AnimationClip>(L"Intro", L"_Textures/RibbyCroaks/shortFrog_intro.png", 15, false, false, 0.1));

	// Attack Rage
	ribby->AddAnimClip(make_shared<AnimationClip>(L"RageS", L"_Textures/RibbyCroaks/shortFrog_rage_start.png", 22, false, false, 0.1));
	ribby->AddAnimClip(make_shared<AnimationClip>(L"RageL", L"_Textures/RibbyCroaks/shortFrog_rage_loop.png", 8, false, true, 0.1));
	ribby->AddAnimClip(make_shared<AnimationClip>(L"RageE", L"_Textures/RibbyCroaks/shortFrog_rage_end.png", 9, false, false, 0.1));

	// Attack Clap
	ribby->AddAnimClip(make_shared<AnimationClip>(L"ClapS", L"_Textures/RibbyCroaks/shortFrog_clap_start.png", 16, true, false, 0.12));
	ribby->AddAnimClip(make_shared<AnimationClip>(L"ClapL", L"_Textures/RibbyCroaks/shortFrog_clap_loop.png", 15, true, false, 0.12));
	ribby->AddAnimClip(make_shared<AnimationClip>(L"ClapE", L"_Textures/RibbyCroaks/shortFrog_clap_end.png", 4, true, false, 0.1));

	// Roll_L
	ribby->AddAnimClip(make_shared<AnimationClip>(L"RollSL", L"_Textures/RibbyCroaks/shortFrog_roll_start_L.png", 14, false, false, 0.1));
	ribby->AddAnimClip(make_shared<AnimationClip>(L"RollLL", L"_Textures/RibbyCroaks/shortFrog_roll_loop_L.png", 8, false, true, 0.1));
	ribby->AddAnimClip(make_shared<AnimationClip>(L"RollEL", L"_Textures/RibbyCroaks/shortFrog_roll_end_L.png", 16, false, false, 0.1));

	// Roll_R
	ribby->AddAnimClip(make_shared<AnimationClip>(L"RollSR", L"_Textures/RibbyCroaks/shortFrog_roll_start_R.png", 14, true, false, 0.1));
	ribby->AddAnimClip(make_shared<AnimationClip>(L"RollLR", L"_Textures/RibbyCroaks/shortFrog_roll_loop_R.png", 8, true, true, 0.1));

	// AddAnimator
	ribby->AddComponent(make_shared<AnimatorComponent>(ribby->GetAnimClips()));
	// animRect SetAnimator
	ribby->SetAnimator(ribby->GET_COMP(Animator));

	// Components
	ribby->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));

	// RibbyBullet
	ribbyAttack = make_shared<RibbyAttackManager>();


	// Croaks
	croaks = make_shared<AnimationRect>(croaksInfo.position, Vector2(450, 583) * croaksInfo.totalSize, 0.0f, L"_Textures/RibbyCroaks/tallfrog_idle_L.png");

	// Move
	// Idle
	croaks->AddAnimClip(make_shared<AnimationClip>(L"IdleL", L"_Textures/RibbyCroaks/tallfrog_idle_L.png", 36, false, true, 0.1));

	// Intro
	croaks->AddAnimClip(make_shared<AnimationClip>(L"Intro", L"_Textures/RibbyCroaks/tallfrog_intro.png", 15, false, false, 0.1));

	// Attack
	croaks->AddAnimClip(make_shared<AnimationClip>(L"SpitS", L"_Textures/RibbyCroaks/tallfrog_spit_start.png", 15, false, false, 0.12));
	croaks->AddAnimClip(make_shared<AnimationClip>(L"SpitR", L"_Textures/RibbyCroaks/tallfrog_spit_rCharge.png", 15, false, false, 0.12));
	croaks->AddAnimClip(make_shared<AnimationClip>(L"Spit", L"_Textures/RibbyCroaks/tallfrog_spit_shoot.png", 8, false, false, 0.1));
	croaks->AddAnimClip(make_shared<AnimationClip>(L"SpitE", L"_Textures/RibbyCroaks/tallfrog_spit_end.png", 14, false, false, 0.12));

	// fan
	croaks->AddAnimClip(make_shared<AnimationClip>(L"FanS", L"_Textures/RibbyCroaks/tallfrog_fan_start.png", 29, false, false, 0.1));
	croaks->AddAnimClip(make_shared<AnimationClip>(L"FanL", L"_Textures/RibbyCroaks/tallfrog_fan_loop.png", 4, false, true, 0.1));
	croaks->AddAnimClip(make_shared<AnimationClip>(L"FanE", L"_Textures/RibbyCroaks/tallfrog_fan_end.png", 14, false, false, 0.1));

	// morph
	croaks->AddAnimClip(make_shared<AnimationClip>(L"MorphS", L"_Textures/RibbyCroaks/tallfrog_morph_start.png", 4, false, false, 0.1));
	croaks->AddAnimClip(make_shared<AnimationClip>(L"MorphL", L"_Textures/RibbyCroaks/tallfrog_morph_loop.png", 3, false, true, 0.1));
	croaks->AddAnimClip(make_shared<AnimationClip>(L"MorphE", L"_Textures/RibbyCroaks/tallfrog_morph_end.png", 25, false, false, 0.1));

	// AddAnimator
	croaks->AddComponent(make_shared<AnimatorComponent>(croaks->GetAnimClips()));
	// animRect SetAnimator
	croaks->SetAnimator(croaks->GET_COMP(Animator));

	// Components
	croaks->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));

	// CroaksBullet
	fireFlyList = make_shared<CroaksAttackManager>(7, 700.0f);

	// CroaksWind
	croaksWind = make_unique<CroaksWind>(300.0f);

	// Sub Collision Rect
	collisionRect = make_unique<ColorRect>(Vector2(1000, -1000), Vector2(1, 1), 0.0f, BLACK);
	collisionRect->AddComponent(make_shared<ColliderComponent>(ColliderType::CIRCLE));
}

void RibbyCroaks::Collision(shared_ptr<Player> player)
{
	if ((rState == RibbyCroaksState::Start2P && ribbyInfo.animCount == 1)
		|| (rState == RibbyCroaksState::Attack && currentPhase == 2))
	{
		if (collisionRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
			player->SetHit(true);
	}
	else if (ribby->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
		player->SetHit(true);
	if (croaks->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
		player->SetHit(true);

	// RibbyFist&player
	for (int i = 0; i < ribbyAttack->GetBullets().size(); ++i)
	{
		if (ribbyAttack->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
		{
			if (ribbyAttack->GetBullets()[i]->GetParrySlap())
			{
				parryTime += DELTA;
				if (parryTime < 0.5f && player->GetParry())
				{
					player->SetJumpSpeed(400.0f);
					player->SetG(0.0f);
					player->SetSuperMeterCard((float)(player->GetSuperMeterCard() + 0.2 * player->GetMaxSuperMeterCard()));	// 20 퍼센트 추가
					ribbyAttack->GetBullets()[i]->SetActivation(false);
					parryTime = 0.0f;
				}
				else if (parryTime >= 0.5f)
				{
					player->SetHit(true);
					parryTime = 0.0f;
				}
			}
			else
			{
				player->SetHit(true);
			}
		}
	}

	// RibbyBall&player
	for (int i = 0; i < ribbyAttack->GetBalls().size(); ++i)
	{
		if (ribbyAttack->GetBalls()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
				player->SetHit(true);
	}

	// CroaksFirefly&player
	for (auto& firefly : fireFlyList->GetBullets())
	{
		if (firefly->GetActivation())
			firefly->Collision(player);
	}

	// CroaksWind&player
	croaksWind->Collision(player);

	// playerBullts&enemies
	for (int i = 0; i < player->GetBullet()->GetBullets().size(); ++i)
	{
		if (player->GetBullet()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(ribby->GET_COMP(Collider))
			|| player->GetBullet()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(croaks->GET_COMP(Collider)))
		{
			if (player->GetBullet()->GetBullets()[i]->GetHit())
			{
				player->GetBullet()->GetBullets()[i]->Hit();
				--hp;
			}
		//	player->GetBullet()->GetBullets()[i]->SetActivation(false);
		}
	}

	for (int i = 0; i < player->GetSpecialAttack()->GetBullets().size(); ++i)
	{
		if (player->GetSpecialAttack()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(ribby->GET_COMP(Collider))
			|| player->GetSpecialAttack()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(croaks->GET_COMP(Collider)))
		{
			--hp;
		}
	}

	if (player->GetSuperBeam()->GetAnimRect()->GET_COMP(Collider)->Intersect(ribby->GET_COMP(Collider))
		|| player->GetSuperBeam()->GetAnimRect()->GET_COMP(Collider)->Intersect(croaks->GET_COMP(Collider)))
		--hp;
}

void RibbyCroaks::Update()
{
	if((int)((float)hp / (float)maxHp * 100) <= SecPhase && currentPhase == 1 
		&& rState == RibbyCroaksState::Idle && cState == RibbyCroaksState::Idle)
	{
		currentPhase = 2;
		phaseIntro = true;
	}
	if((int)((float)hp / (float)maxHp * 100) <= thrPhase && currentPhase == 2 
		&& rState == RibbyCroaksState::Idle && cState == RibbyCroaksState::Idle)
	{
		currentPhase = 3;
		phaseIntro = true;
	}

	if (bMod)
	{
		if (!(ImGui::IsAnyItemActive()) && ribby->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			ribbyInfo.position = INPUT->GetMousePosition();
		else if (!(ImGui::IsAnyItemActive()) && croaks->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			croaksInfo.position = INPUT->GetMousePosition();

		ribby->SetPosition(ribbyInfo.position);
		croaks->SetPosition(croaksInfo.position);
		hp = 510;
		phaseIntro = false;
		croaksInfo.bIntro = true;
		ribbyInfo.bIntro = false;
	}

	ribbyInfo.time += DELTA;
	croaksInfo.time += DELTA;

	// Idle
	rState = RibbyCroaksState::Idle;
	cState = RibbyCroaksState::Idle;

	// Intro
	if (croaksInfo.bIntro)
		cState = RibbyCroaksState::Intro;
	else if (ribbyInfo.bIntro)
		rState = RibbyCroaksState::Intro;

	// attack
	if (rState != RibbyCroaksState::Intro && cState != RibbyCroaksState::Intro)
	{
		if (ribbyInfo.time >= delay && ribbyInfo.bAttack)
			rState = RibbyCroaksState::Attack;
		if (croaksInfo.time >= delay && croaksInfo.bAttack)
			cState = RibbyCroaksState::Attack;
	}


	// nextPhase Intro
	if (currentPhase == 2 && phaseIntro && rState == RibbyCroaksState::Idle && cState == RibbyCroaksState::Idle)
	{
		rState = RibbyCroaksState::Start2P;
		croaksInfo.bAttack = false;
		ribbyInfo.bAttack = false;
	}
	else if (currentPhase == 3 && phaseIntro && (rState == RibbyCroaksState::Idle || rState == RibbyCroaksState::None) && cState == RibbyCroaksState::Idle)
	{
		rState = RibbyCroaksState::Start3P;
		cState = RibbyCroaksState::Start3P;
		croaksInfo.bAttack = false;
		ribbyInfo.bAttack = false;
	}

	if (bNone)
		rState = RibbyCroaksState::None;

	// Ribby
	switch (rState)
	{
	case  RibbyCroaksState::None:
		ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"IdleL");
		ribby->SetScale(Vector2(370, 350) * ribbyInfo.totalSize);
		ribbyInfo.position = Vector2(1000, -1000);
		ribby->SetPosition(ribbyInfo.position);
		break;
	case RibbyCroaksState::Idle:
		if (currentPhase == 1)
		{
			ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"IdleL");
			ribby->SetScale(Vector2(370, 350) * ribbyInfo.totalSize);
			ribby->SetPosition(ribbyInfo.position);
		}
		else if (currentPhase == 2)
		{
			ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"IdleR");
			ribby->SetScale(Vector2(370, 350) * ribbyInfo.totalSize);
			ribby->SetPosition(ribbyInfo.position);
		}

		break;
	case RibbyCroaksState::Attack:
		if (currentPhase == 1)
		{
			if (ribbyInfo.animCount == 0)
			{
				ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"RageS");
				ribby->SetScale(Vector2(570, 463) * ribbyInfo.totalSize);
				ribby->SetPosition(Vector2(ribbyInfo.position.x - 45 * ribbyInfo.totalSize, ribbyInfo.position.y + 55 * ribbyInfo.totalSize));
				if (ribby->GET_COMP(Animator)->GetEnd())
				{
					++ribbyInfo.animCount;
					ribbyAttack->Init(9, 900.0f, Vector2(ribby->GetPosition().x - 100 * ribbyInfo.totalSize, ribby->GetPosition().y - 150.0f * ribbyInfo.totalSize), -180.0f, currentPhase);
				}
			}
			else if (ribbyInfo.animCount == 1)
			{
				ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"RageL");
				ribby->SetScale(Vector2(515, 395) * ribbyInfo.totalSize);
				ribby->SetPosition(Vector2(ribbyInfo.position.x - 87 * ribbyInfo.totalSize, ribbyInfo.position.y + 26 * ribbyInfo.totalSize));
				if (ribbyAttack->GetEnd())
					++ribbyInfo.animCount;
			}
			else
			{
				ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"RageE");
				ribby->SetScale(Vector2(490, 340) * ribbyInfo.totalSize);
				ribby->SetPosition(Vector2(ribbyInfo.position.x - 70 * ribbyInfo.totalSize, ribbyInfo.position.y - 3 * ribbyInfo.totalSize));
				if (ribby->GET_COMP(Animator)->GetEnd())
				{
					ribbyInfo.time = 0.0f;
					croaksInfo.time = 0.0f;
					ribbyInfo.animCount = 0.0f;
					ribbyInfo.bAttack = false;
					croaksInfo.bAttack = true;
				}
			}
		}
		else if (currentPhase == 2)
		{
			if (ribbyInfo.animCount == 0)
			{
				ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"ClapS");
				ribby->SetScale(Vector2(575, 405) * ribbyInfo.totalSize);
				ribby->SetPosition(Vector2(ribbyInfo.position.x + 95 * ribbyInfo.totalSize, ribbyInfo.position.y + 14 * ribbyInfo.totalSize));
				// CollisionRect
				collisionRect->SetPosition(Vector2(ribby->GetPosition().x - 95 * ribbyInfo.totalSize, ribby->GetPosition().y));
				collisionRect->SetScale(Vector2(ribby->GetScale().x - 115.0f, ribby->GetScale().y - 35.0f));
				collisionRect->GET_COMP(Collider)->SetType(ColliderType::RECT);
				if (ribby->GET_COMP(Animator)->GetCurrentFrameIndex() <= 1 && !ribbyInfo.bFrame)
				{
					ribbyAttack->Init(3, 650.0f, Vector2(ribby->GetPosition().x + 100 * ribbyInfo.totalSize, ribby->GetPosition().y - 20.0f * ribbyInfo.totalSize), 0.0f, currentPhase);
					ribbyAttack->InitBall();
					ribbyInfo.bFrame = true;
				}
				if (ribby->GET_COMP(Animator)->GetEnd())
				{
					ribbyInfo.bFrame = false;
					++ribbyInfo.animCount;
					collisionRect->SetPosition(Vector2(1000, -1000));
				}
			}
			else if (ribbyInfo.animCount == 1)
			{
				ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"ClapL");
				ribby->SetScale(Vector2(575, 405) * ribbyInfo.totalSize);
				ribby->SetPosition(Vector2(ribbyInfo.position.x + 98 * ribbyInfo.totalSize, ribbyInfo.position.y + 10 * ribbyInfo.totalSize));
				// CollisionRect
				collisionRect->SetPosition(Vector2(ribby->GetPosition().x - 85 * ribbyInfo.totalSize, ribby->GetPosition().y));
				collisionRect->SetScale(Vector2(ribby->GetScale().x - 115.0f, ribby->GetScale().y - 35.0f));
				collisionRect->GET_COMP(Collider)->SetType(ColliderType::RECT);
				if (ribby->GET_COMP(Animator)->GetCurrentFrameIndex() <= 1 && !ribbyInfo.bFrame)
				{
					ribbyAttack->InitBall();
					ribbyInfo.bFrame = true;
				}
				if (ribby->GET_COMP(Animator)->GetEnd())
				{
					ribbyInfo.bFrame = false;
					if (ribbyAttack->GetEnd())
					{
						++ribbyInfo.animCount;
						collisionRect->SetPosition(Vector2(1000, -1000));
					}
					else
						ribby->GET_COMP(Animator)->ResetFrame();
				}
			}
			else
			{
				ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"ClapE");
				ribby->SetScale(Vector2(575, 405) * ribbyInfo.totalSize);
				ribby->SetPosition(Vector2(ribbyInfo.position.x + 100 * ribbyInfo.totalSize, ribbyInfo.position.y + 10 * ribbyInfo.totalSize));
				// CollisionRect
				collisionRect->SetPosition(Vector2(ribby->GetPosition().x - 120 * ribbyInfo.totalSize, ribby->GetPosition().y));
				collisionRect->SetScale(Vector2(ribby->GetScale().x - 195.0f, ribby->GetScale().y - 65.0f));
				collisionRect->GET_COMP(Collider)->SetType(ColliderType::RECT);
				if (ribby->GET_COMP(Animator)->GetEnd())
				{
					ribbyInfo.time = 0.0f;
					ribbyInfo.animCount = 0.0f;
					rState = RibbyCroaksState::Idle;
					collisionRect->SetPosition(Vector2(1000, -1000));
				}
			}
		}
		break;
	case RibbyCroaksState::Intro:
		if (ribbyInfo.bIntro && ribbyInfo.time >= 1.0f)
		{
			ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"Intro");
			ribby->SetScale(Vector2(482, 490) * ribbyInfo.totalSize);
			ribby->SetPosition(Vector2(ribbyInfo.position.x + 26 * ribbyInfo.totalSize, ribbyInfo.position.y + 54 * ribbyInfo.totalSize));
			if (ribby->GET_COMP(Animator)->GetEnd())
			{
				ribbyInfo.bIntro = false;
				ribbyInfo.time = 2.0f;
				croaksInfo.time = 2.0f;

				uniform_int_distribution<int> randomAttack(0, 1);
				if (randomAttack(mt))
					this->ribbyInfo.bAttack = true;
				else
					this->croaksInfo.bAttack = true;
			}
		}
		break;
	case RibbyCroaksState::Start2P:
		if (ribbyInfo.animCount == 0)
		{
			ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"RollSL");
			ribby->SetScale(Vector2(420, 335) * ribbyInfo.totalSize);
			ribby->SetPosition(Vector2(ribbyInfo.position.x - 20 * ribbyInfo.totalSize, ribbyInfo.position.y - 47 * ribbyInfo.totalSize));
			if (ribby->GET_COMP(Animator)->GetEnd())
			{
				ribby->GET_COMP(Animator)->ResetFrame();
				++ribbyInfo.animCount;
				ribbyInfo.time = 0.0f;
			}
		}
		else if (ribbyInfo.animCount == 1)
		{
			ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"RollLL");
			ribby->SetScale(Vector2(610, 260) * ribbyInfo.totalSize);
			ribby->SetPosition(Vector2(ribbyInfo.position.x + 65 * ribbyInfo.totalSize, ribbyInfo.position.y - 55 * ribbyInfo.totalSize));
			collisionRect->SetPosition(Vector2(ribby->GetPosition().x - 153 * ribbyInfo.totalSize, ribby->GetPosition().y));
			collisionRect->SetScale(Vector2(ribby->GetScale().y - 48, ribby->GetScale().y - 48));
			collisionRect->GET_COMP(Collider)->SetType(ColliderType::CIRCLE);
			if (ribbyInfo.time > 1.0f)
				ribbyInfo.position.x -= ribbyInfo.time * 2;
			if (ribby->GetPosition().x + ribby->GetScale().x * 0.5f < CAMERA->GetPosition().x)
			{
				++ribbyInfo.animCount;
				ribbyInfo.position.x = 85.0f;
				collisionRect->SetPosition(Vector2(1000, -1000));
			}
		}
		else
		{
			ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"RollEL");
			ribby->SetScale(Vector2(480, 300) * ribbyInfo.totalSize);
			ribby->SetPosition(Vector2(ribbyInfo.position.x - 68 * ribbyInfo.totalSize, ribbyInfo.position.y - 31 * ribbyInfo.totalSize));
			if (ribby->GET_COMP(Animator)->GetEnd())
			{
				ribbyInfo.time = 0.0f;
				ribbyInfo.animCount = 0;
				phaseIntro = false;
				currentPhase = 2;
				ribbyInfo.bAttack = true;
				croaksInfo.bAttack = true;
			}
		}
		break;
	case RibbyCroaksState::Start3P:
		if (ribbyInfo.animCount == 0)
		{
			ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"RollSR");
			ribby->SetScale(Vector2(420, 335) * ribbyInfo.totalSize);
			ribby->SetPosition(Vector2(ribbyInfo.position.x - 10 * ribbyInfo.totalSize, ribbyInfo.position.y - 47 * ribbyInfo.totalSize));
			if (ribby->GET_COMP(Animator)->GetEnd())
			{
				ribby->GET_COMP(Animator)->ResetFrame();
				++ribbyInfo.animCount;
				ribbyInfo.time = 1.0f;
			}
		}
		else if (ribbyInfo.animCount == 1)
		{
			ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"RollLR");
			ribby->SetScale(Vector2(610, 260) * ribbyInfo.totalSize);
			ribby->SetPosition(Vector2(ribbyInfo.position.x - 95 * ribbyInfo.totalSize, ribbyInfo.position.y - 55 * ribbyInfo.totalSize));
			// CollisionRect
			collisionRect->SetPosition(Vector2(ribby->GetPosition().x + 153 * ribbyInfo.totalSize, ribby->GetPosition().y));
			collisionRect->SetScale(Vector2(ribby->GetScale().y - 48, ribby->GetScale().y - 48));
			collisionRect->GET_COMP(Collider)->SetType(ColliderType::CIRCLE);
			ribbyInfo.position.x += ribbyInfo.time * 2;
			ribbyInfo.position.y += ribbyInfo.time / 8;
		}
		else
		{
			ribbyInfo.time = 0.0f;
			ribbyInfo.animCount = 0;
			collisionRect->SetPosition(Vector2(1000, -1000));
			bNone = true;
		}

		break;
	}

	// Croaks
	switch (cState)
	{
	case RibbyCroaksState::Idle:
		if (currentPhase == 3)
		{
		//	croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"SIdle");
		//	croaks->SetScale(Vector2(450, 583)* croaksInfo.totalSize);
		//	croaks->SetPosition(croaksInfo.position);
		}
		else
		{
			croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"IdleL");
			croaks->SetScale(Vector2(450, 583)* croaksInfo.totalSize);
			croaks->SetPosition(croaksInfo.position);
		}
		break;
	case RibbyCroaksState::Attack:
		if (currentPhase == 1)
		{
			if (croaksInfo.animCount == 0)
			{
				croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"SpitS");
				croaks->SetScale(Vector2(545, 650) * croaksInfo.totalSize);
				croaks->SetPosition(Vector2(croaksInfo.position.x + 55 * croaksInfo.totalSize, croaksInfo.position.y + 37 * croaksInfo.totalSize));
				if (croaks->GET_COMP(Animator)->GetEnd())
				{
					++croaksInfo.animCount;
					fireFlyList->InitSize();

					uniform_int_distribution<int> randomCount(1, 2);
					count = randomCount(mt);
				}
			}
			else if (croaksInfo.animCount == 1)
			{
				croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"Spit");
				croaks->SetScale(Vector2(500, 540) * croaksInfo.totalSize);
				croaks->SetPosition(Vector2(croaksInfo.position.x - 15 * croaksInfo.totalSize, croaksInfo.position.y - 25 * croaksInfo.totalSize));
				if (croaks->GET_COMP(Animator)->GetCurrentFrameIndex() == 4 && !croaksInfo.bFrame)
				{
					fireFlyList->InitPos(croaksInfo.position);
					croaksInfo.bFrame = true;
				}
				if (croaks->GET_COMP(Animator)->GetEnd())
				{
					croaksInfo.bFrame = false;
					--count;
					if (count == 0)
					{
						if (fireFlyList->Remainder() == 0)
							croaksInfo.animCount += 2;
						else
							++croaksInfo.animCount;
					}
					else
						croaks->GET_COMP(Animator)->ResetFrame();
				}
			}
			else if (croaksInfo.animCount == 2)
			{
				croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"SpitR");
				croaks->SetScale(Vector2(545, 650) * croaksInfo.totalSize);
				croaks->SetPosition(Vector2(croaksInfo.position.x + 22 * croaksInfo.totalSize, croaksInfo.position.y + 27 * croaksInfo.totalSize));
				if (croaks->GET_COMP(Animator)->GetEnd())
				{
					if (fireFlyList->Remainder() == 1)
						count = 1;
					else
					{
						uniform_int_distribution<int> randomCount(1, 2);
						count = randomCount(mt);
					}
					--croaksInfo.animCount;
				}
			}
			else
			{
				croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"SpitE");
				croaks->SetScale(Vector2(550, 630) * croaksInfo.totalSize);
				croaks->SetPosition(Vector2(croaksInfo.position.x + 18 * croaksInfo.totalSize, croaksInfo.position.y + 22 * croaksInfo.totalSize));
				if (croaks->GET_COMP(Animator)->GetEnd())
				{
					croaksInfo.time = 0.0f;
					ribbyInfo.time = 0.0f;
					croaksInfo.animCount = 0;
					ribbyInfo.bAttack = true;
					croaksInfo.bAttack = false;
				}
			}
		}
		else if (currentPhase == 2)
		{
			if (croaksInfo.animCount == 0)
			{
				croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"FanS");
				croaks->SetScale(Vector2(610, 710)* croaksInfo.totalSize);
				croaks->SetPosition(Vector2(croaksInfo.position.x + 50 * croaksInfo.totalSize, croaksInfo.position.y + 30 * croaksInfo.totalSize));
				if (croaks->GET_COMP(Animator)->GetCurrentFrameIndex() == 24 && !croaksInfo.bFrame)
				{
					croaksWind->Init(Vector2(croaksInfo.position.x - 430, croaksInfo.position.y + 55), croaksInfo.totalSize);
					croaksInfo.bFrame = true;
				}
				if (croaks->GET_COMP(Animator)->GetEnd())
				{
					++croaksInfo.animCount;
					deltaTime = 0.0f;
					croaksInfo.bFrame = false;
					croaksWind->Init(Vector2(croaksInfo.position.x - 430, croaksInfo.position.y + 55), croaksInfo.totalSize);
				}
			}
			else if (croaksInfo.animCount == 1)
			{
				deltaTime += DELTA;
				croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"FanL");
				croaks->SetScale(Vector2(370, 670) * croaksInfo.totalSize);
				croaks->SetPosition(Vector2(croaksInfo.position.x - 35 * croaksInfo.totalSize, croaksInfo.position.y + 11 * croaksInfo.totalSize));
				
				// Move
				if ((int)croaks->GetPosition().x < 1140)
				{
					float tempX = 1140.0f - croaksInfo.position.x;
					croaksInfo.position.x += tempX * DELTA;
				}

				if (deltaTime >= 8.0f)
				{
					++croaksInfo.animCount;
					deltaTime = 0.0f;
					croaksWind->Init(Vector2(croaksInfo.position.x - 430, croaksInfo.position.y + 55), croaksInfo.totalSize);
				}
			}
			else
			{
				croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"FanE");
				croaks->SetScale(Vector2(460, 610) * croaksInfo.totalSize);
				croaks->SetPosition(Vector2(croaksInfo.position.x - 13 * croaksInfo.totalSize, croaksInfo.position.y + 15 * croaksInfo.totalSize));
				if (croaks->GET_COMP(Animator)->GetEnd())
				{
					croaksInfo.animCount = 0;
					croaksInfo.time = 0.0f;
				}
			}
		}
		break;
	case RibbyCroaksState::Intro:
		if (croaksInfo.bIntro && croaksInfo.time >= 2.0f)
		{
			croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"Intro");
			croaks->SetScale(Vector2(570, 583) * croaksInfo.totalSize);
			croaks->SetPosition(Vector2(croaksInfo.position.x - 53 * croaksInfo.totalSize, croaksInfo.position.y));
			if (croaks->GET_COMP(Animator)->GetEnd())
			{
				croaksInfo.bIntro = false;
				ribbyInfo.bIntro = true;
				croaksInfo.time = 0.0f;
				ribbyInfo.time = 0.0f;
				cState = RibbyCroaksState::Idle;
			}
		}
		break;
	case RibbyCroaksState::Start3P:
		if (croaksInfo.animCount == 0)
		{
			croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"MorphS");
			croaks->SetScale(Vector2(505, 425) * 1.22 * croaksInfo.totalSize);
			croaks->SetPosition(Vector2(croaksInfo.position.x - 74 * croaksInfo.totalSize, croaksInfo.position.y - 57 * croaksInfo.totalSize));
			if (croaks->GET_COMP(Animator)->GetEnd())
			{
				++croaksInfo.animCount;
			}
		}
		else if (croaksInfo.animCount == 1)
		{
			croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"MorphL");
			croaks->SetScale(Vector2(513, 289) * 1.22 * croaksInfo.totalSize);
			croaks->SetPosition(Vector2(croaksInfo.position.x - 60 * croaksInfo.totalSize, croaksInfo.position.y - 140 * croaksInfo.totalSize));

			// ribby가 해당 위치에 도착했을 때 end
			if (ribby->GetPosition().x >= croaks->GetPosition().x - croaks->GetScale().x * 0.5 - 100)
			{
				// ribby 초기화 및 비활성화
				++ribbyInfo.animCount;

				++croaksInfo.animCount;
			}
		}
		else
		{
			croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"MorphE");
			croaks->SetScale(Vector2(800, 735) * 1.2 * croaksInfo.totalSize);
			croaks->SetPosition(Vector2(croaksInfo.position.x - 90 * croaksInfo.totalSize, croaksInfo.position.y + 75 * croaksInfo.totalSize));
			if (croaks->GET_COMP(Animator)->GetEnd())
			{
				croaksInfo.animCount = 0;
				phaseIntro = false;
			}
		}
		break;
	}

	ribbyAttack->SetTotalSize(ribbyInfo.totalSize);
	fireFlyList->SetTotalSize(croaksInfo.totalSize);
	croaks->Update();
	ribby->Update();
	ribbyAttack->Update();
	fireFlyList->Update();
	croaksWind->Update();
	if (collisionRect->GetPosition().y != -1000)
		collisionRect->Update();
}

void RibbyCroaks::Render()
{
	fireFlyList->Render();
	croaks->Render();
	croaksWind->Render();
	ribbyAttack->Render();
//	if (collisionRect->GetPosition().y != -1000)
//		collisionRect->Render();
	if (!bNone)
		ribby->Render();
}

void RibbyCroaks::GUI()
{
	static bool bOpen = true;
	if (ImGui::Begin("RibbyCroaks", &bOpen))
	{
		ImGui::InputInt("MaxHp", (int*)&maxHp);
		ImGui::InputFloat("Delay", &delay);

		ImGui::SliderFloat("SecondPhase", &SecPhase, 30.0f, 90.0f, "%.0f");
		ImGui::SliderFloat("ThirdPhase", &thrPhase, 10.0f, (SecPhase - 10.0f), "%.0f");

		string text = "Ribby";
		ImGui::Text(text.c_str());
		ImGui::SliderFloat2("RPosition", (float*)&ribbyInfo.position, CAMERA->GetPosition().x, CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH);
		ImGui::SliderFloat("RScale", &ribbyInfo.totalSize, 0.0f, 2.0f, "%.1f");
	
		text = "Croaks";
		ImGui::Text(text.c_str());
		ImGui::SliderFloat2("CPosition", (float*)&croaksInfo.position, CAMERA->GetPosition().x, CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH);
		ImGui::SliderFloat("CScale", &croaksInfo.totalSize, 0.0f, 2.0f, "%.1f");
	}
	ImGui::End();
}
