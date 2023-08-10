#include "stdafx.h"
#include "RibbyCroaks.h"

RibbyCroaks::RibbyCroaks(RibbyCroaksInfo ribbyInfo, RibbyCroaksInfo croaksInfo, UINT maxHp, float delay)
	: ribbyInfo(ribbyInfo), croaksInfo(croaksInfo), maxHp(maxHp), delay(delay)
{
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

	// Attack
	ribby->AddAnimClip(make_shared<AnimationClip>(L"RageS", L"_Textures/RibbyCroaks/shortFrog_rage_start.png", 22, false, false, 0.1));
	ribby->AddAnimClip(make_shared<AnimationClip>(L"RageL", L"_Textures/RibbyCroaks/shortFrog_rage_loop.png", 8, false, true, 0.1));
	ribby->AddAnimClip(make_shared<AnimationClip>(L"RageE", L"_Textures/RibbyCroaks/shortFrog_rage_end.png", 9, false, false, 0.1));

	// AddAnimator
	ribby->AddComponent(make_shared<AnimatorComponent>(ribby->GetAnimClips()));
	// animRect SetAnimator
	ribby->SetAnimator(ribby->GET_COMP(Animator));

	// Components
	ribby->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));

	// RibbyBullet
	fistList = make_shared<RibbyFistManager>(9, 900.0f, 90.0f * ribbyInfo.totalSize);


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

	// AddAnimator
	croaks->AddComponent(make_shared<AnimatorComponent>(croaks->GetAnimClips()));
	// animRect SetAnimator
	croaks->SetAnimator(croaks->GET_COMP(Animator));

	// Components
	croaks->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));

	// CroaksBullet
	fireFlyList = make_shared<CroaksAttackManager>(7, 700.0f);
}

void RibbyCroaks::Collision(shared_ptr<Player> player)
{
	if (ribby->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider))
		|| croaks->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
		player->SetHit(true);

	// RibbyFist&player Collision
	for (int i = 0; i < fistList->GetBullets().size(); ++i)
	{
		if (fistList->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
		{
			if (fistList->GetBullets()[i]->GetParrySlap())
			{
				parryTime += DELTA;
				if (parryTime < 0.5f && player->GetParry())
				{
					player->SetJumpSpeed(400.0f);
					player->SetG(0.0f);
					player->SetSuperMeterCard((float)(player->GetSuperMeterCard() + 0.2 * player->GetMaxSuperMeterCard()));	// 20 퍼센트 추가
					fistList->GetBullets()[i]->SetActivation(false);
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

	// Firefly&player Collision
	for (auto& firefly : fireFlyList->GetBullets())
	{
		if (firefly->GetActivation())
			firefly->Collision(player);
	}

	// playerBullts&enemies Collision
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
	if (bMod)
	{
		if (!(ImGui::IsAnyItemActive()) && ribby->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			ribbyInfo.position = INPUT->GetMousePosition();
		else if (!(ImGui::IsAnyItemActive()) && croaks->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			croaksInfo.position = INPUT->GetMousePosition();

		ribby->SetPosition(ribbyInfo.position);
		croaks->SetPosition(croaksInfo.position);
		hp = maxHp;
		croaksInfo.bIntro = true;
		ribbyInfo.bIntro = false;
	}

	time += DELTA;

	rState = RibbyCroaksState::Idle;
	cState = RibbyCroaksState::Idle;

	if (croaksInfo.bIntro)
		cState = RibbyCroaksState::Intro;
	else if (ribbyInfo.bIntro)
		rState = RibbyCroaksState::Intro;
	else if (time >= delay)
	{
		if (ribbyInfo.bAttack)
			rState = RibbyCroaksState::Attack;
		else if (croaksInfo.bAttack)
			cState = RibbyCroaksState::Attack;
	}

	// Ribby
	switch (rState)
	{
	case RibbyCroaksState::Idle:
		ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"IdleL");
		ribby->SetScale(Vector2(370, 350) * ribbyInfo.totalSize);
		ribby->SetPosition(ribbyInfo.position);
		break;
	case RibbyCroaksState::Attack:
		if (check == 0)
		{
			ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"RageS");
			ribby->SetScale(Vector2(570, 463) * ribbyInfo.totalSize);
			ribby->SetPosition(Vector2(ribbyInfo.position.x - 45 * ribbyInfo.totalSize, ribbyInfo.position.y + 55 * ribbyInfo.totalSize));
			if (ribby->GET_COMP(Animator)->GetEnd())
			{
				++check;
				fistList->Init(Vector2(ribby->GetPosition().x - 100 * ribbyInfo.totalSize, ribby->GetPosition().y - 150.0f * ribbyInfo.totalSize), -180.0f);
			}
		}
		else if (check == 1)
		{
			ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"RageL");
			ribby->SetScale(Vector2(515, 395) * ribbyInfo.totalSize);
			ribby->SetPosition(Vector2(ribbyInfo.position.x - 87 * ribbyInfo.totalSize, ribbyInfo.position.y + 26 * ribbyInfo.totalSize));
			if (fistList->GetEnd())
				++check;
		}
		else
		{
			ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"RageE");
			ribby->SetScale(Vector2(490, 340) * ribbyInfo.totalSize);
			ribby->SetPosition(Vector2(ribbyInfo.position.x - 70 * ribbyInfo.totalSize, ribbyInfo.position.y - 3 * ribbyInfo.totalSize));
			if (ribby->GET_COMP(Animator)->GetEnd())
			{
				time = 0.0f;
				check = 0.0f;
				ribbyInfo.bAttack = false;
				croaksInfo.bAttack = true;
			}
		}
		break;
	case RibbyCroaksState::Intro:
		if (ribbyInfo.bIntro && time >= 1.0f)
		{
			ribby->GET_COMP(Animator)->SetCurrentAnimClip(L"Intro");
			ribby->SetScale(Vector2(482, 490) * ribbyInfo.totalSize);
			ribby->SetPosition(Vector2(ribbyInfo.position.x + 26 * ribbyInfo.totalSize, ribbyInfo.position.y + 54 * ribbyInfo.totalSize));
			if (ribby->GET_COMP(Animator)->GetEnd())
			{
				ribbyInfo.bIntro = false;
				time = 2.0f;

				uniform_int_distribution<int> randomAttack(0, 1);
				if (randomAttack(mt))
					this->ribbyInfo.bAttack = true;
				else
					this->croaksInfo.bAttack = true;
			}
		}
		break;
	case RibbyCroaksState::Start2P:
		break;
	case RibbyCroaksState::Start3P:
		break;
	}

	// Croaks
	switch (cState)
	{
	case RibbyCroaksState::Idle:
		croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"IdleL");
		croaks->SetScale(Vector2(450, 583) * croaksInfo.totalSize);
		croaks->SetPosition(croaksInfo.position);
		break;
	case RibbyCroaksState::Attack:
		if (check == 0)
		{
			croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"SpitS");
			croaks->SetScale(Vector2(545, 650)* croaksInfo.totalSize);
			croaks->SetPosition(Vector2(croaksInfo.position.x + 55 * croaksInfo.totalSize, croaksInfo.position.y + 37 * croaksInfo.totalSize));
			if (croaks->GET_COMP(Animator)->GetEnd())
			{
				++check;
				fireFlyList->InitSize();

				uniform_int_distribution<int> randomCount(1, 2);
				count = randomCount(mt);
			}
		}
		else if (check == 1)
		{
			croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"Spit");
			croaks->SetScale(Vector2(500, 540)* croaksInfo.totalSize);
			croaks->SetPosition(Vector2(croaksInfo.position.x - 15 * croaksInfo.totalSize, croaksInfo.position.y - 25 * croaksInfo.totalSize));
			if (croaks->GET_COMP(Animator)->GetCurrentFrameIndex() == 4 && !bFrame)
			{
				fireFlyList->InitPos(croaksInfo.position);
				bFrame = true;
			}
			if (croaks->GET_COMP(Animator)->GetEnd())
			{
				bFrame = false;
				--count;
				if (count == 0)
				{
					if (fireFlyList->Remainder() == 0)
						check += 2;
					else
						++check;
				}
				else
					croaks->GET_COMP(Animator)->ResetFrame();
			}
		}
		else if (check == 2)
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
				--check;
			}
		}
		else
		{
			croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"SpitE");
			croaks->SetScale(Vector2(550, 630) * croaksInfo.totalSize);
			croaks->SetPosition(Vector2(croaksInfo.position.x + 18 * croaksInfo.totalSize, croaksInfo.position.y + 22 * croaksInfo.totalSize));
			if (croaks->GET_COMP(Animator)->GetEnd())
			{
				time = 0.0f;
				check = 0.0f;
				ribbyInfo.bAttack = true;
				croaksInfo.bAttack = false;
			}
		}
		break;
	case RibbyCroaksState::Intro:
		if (croaksInfo.bIntro && time >= 2.0f)
		{
			croaks->GET_COMP(Animator)->SetCurrentAnimClip(L"Intro");
			croaks->SetScale(Vector2(570, 583) * croaksInfo.totalSize);
			croaks->SetPosition(Vector2(croaksInfo.position.x - 53 * croaksInfo.totalSize, croaksInfo.position.y));
			if (croaks->GET_COMP(Animator)->GetEnd())
			{
				croaksInfo.bIntro = false;
				ribbyInfo.bIntro = true;
				time = 0.0f;
				cState = RibbyCroaksState::Idle;
			}
		}
		break;
	case RibbyCroaksState::Start2P:
		break;
	case RibbyCroaksState::Start3P:
		break;
	}

	fistList->SetTotalSize(ribbyInfo.totalSize);
	fireFlyList->SetTotalSize(croaksInfo.totalSize);
	croaks->Update();
	ribby->Update();
	fistList->Update();
	fireFlyList->Update();
}

void RibbyCroaks::Render()
{
	fireFlyList->Render();
	croaks->Render();
	fistList->Render();
	ribby->Render();
}

void RibbyCroaks::GUI()
{
	static bool bOpen = true;
	if (ImGui::Begin("RibbyCroaks", &bOpen))
	{
		ImGui::InputInt("MaxHp", (int*)&maxHp);
		ImGui::InputFloat("Delay", &delay);

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
