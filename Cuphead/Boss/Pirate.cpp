#include "stdafx.h"
#include "Pirate.h"

Pirate::Pirate(PirateInfo captainInfo, PirateInfo boatInfo, UINT maxHp, float waveValue)
	: captainInfo(captainInfo), boatInfo(boatInfo), maxHp(maxHp), waveValue(waveValue)
{
	// �ʱ�ȭ
	hp = maxHp;
	bIntro = true;
	random_device random;
	mt = mt19937(random());

	speed = waveValue * 0.5f;
	defPos = boatInfo.position;

	captain = make_shared<AnimationRect>(boatInfo.position + captainInfo.position * captainInfo.totalSize, Vector2(370, 350) * captainInfo.totalSize, 0.0f, L"_Textures/Pirate/pirate_idle.png");
	tCaptain = make_shared<AnimationRect>(boatInfo.position + captainInfo.position * captainInfo.totalSize, Vector2(580, 465) * captainInfo.totalSize, 0.0f, L"_Textures/Pirate/pirate_peaPutDown_T.png");
	fBoat = make_shared<AnimationRect>(boatInfo.position, Vector2(450, 583) * boatInfo.totalSize, 0.0f, L"_Textures/Pirate/pirate_boat_idle.png");
	fRail = make_shared<AnimationRect>(boatInfo.position, Vector2(164, 80) * boatInfo.totalSize, 0.0f, L"_Textures/Pirate/pirate_boatRail.png");
	bBoat = make_shared<AnimationRect>(boatInfo.position, Vector2(529, 412) * boatInfo.totalSize, 0.0f, L"_Textures/Pirate/pirate_boatSail.png");
	
	// Captain
	// Idle
	captain->AddAnimClip(make_shared<AnimationClip>(L"Idle", L"_Textures/Pirate/pirate_idle.png", 12, false, true, 0.12));

	// Intro
	captain->AddAnimClip(make_shared<AnimationClip>(L"IntroS", L"_Textures/Pirate/pirate_laugh_start.png", 4, false, false, 0.1));
	captain->AddAnimClip(make_shared<AnimationClip>(L"IntroL", L"_Textures/Pirate/pirate_laugh_loop.png", 8, false, false, 0.1));
	captain->AddAnimClip(make_shared<AnimationClip>(L"IntroE", L"_Textures/Pirate/pirate_laugh_end.png", 2, false, false, 0.1));

	// Attack
	captain->AddAnimClip(make_shared<AnimationClip>(L"PShotS", L"_Textures/Pirate/pirate_peaPickup.png", 21, false, false, 0.1));
	captain->AddAnimClip(make_shared<AnimationClip>(L"PShotI", L"_Textures/Pirate/pirate_peaShot_idle.png", 5, false, true, 0.12));
	captain->AddAnimClip(make_shared<AnimationClip>(L"PShot", L"_Textures/Pirate/pirate_peaShot.png", 10, false, false, 0.1));
	captain->AddAnimClip(make_shared<AnimationClip>(L"PShotE", L"_Textures/Pirate/pirate_peaPutDown.png", 13, false, false, 0.1));

	// Whistle
	captain->AddAnimClip(make_shared<AnimationClip>(L"Whistle01", L"_Textures/Pirate/pirate_whistle_01.png", 10, false, false, 0.1));
	captain->AddAnimClip(make_shared<AnimationClip>(L"Whistle02", L"_Textures/Pirate/pirate_whistle_02.png", 10, false, false, 0.1));
	captain->AddAnimClip(make_shared<AnimationClip>(L"Whistle03", L"_Textures/Pirate/pirate_whistle_03.png", 10, false, false, 0.1));
	captain->AddAnimClip(make_shared<AnimationClip>(L"Whistle04", L"_Textures/Pirate/pirate_whistle_04.png", 10, false, false, 0.1));
	captain->AddAnimClip(make_shared<AnimationClip>(L"Whistle05", L"_Textures/Pirate/pirate_whistle_05.png", 11, false, false, 0.1));

	// TCaptain
	// Attack
	tCaptain->AddAnimClip(make_shared<AnimationClip>(L"TPShotS", L"_Textures/Pirate/pirate_peaPickup_T.png", 21, false, false, 0.1));
	tCaptain->AddAnimClip(make_shared<AnimationClip>(L"TPShotI", L"_Textures/Pirate/pirate_peaShot_idle_T.png", 5, false, true, 0.12));
	tCaptain->AddAnimClip(make_shared<AnimationClip>(L"TPShot", L"_Textures/Pirate/pirate_peaShot_T.png", 10, false, false, 0.1));
	tCaptain->AddAnimClip(make_shared<AnimationClip>(L"TPShotE", L"_Textures/Pirate/pirate_peaPutDown_T.png", 13, false, false, 0.1));

	// fBoat
	// Idle
	fBoat->AddAnimClip(make_shared<AnimationClip>(L"Idle", L"_Textures/Pirate/pirate_boat_idle.png", 3, false, true, 0.1));

	// Intro

	// Attack
	fBoat->AddAnimClip(make_shared<AnimationClip>(L"Attack01", L"_Textures/Pirate/pirate_boat_cannon_01.png", 10, false, false, 0.1));
	fBoat->AddAnimClip(make_shared<AnimationClip>(L"Attack02", L"_Textures/Pirate/pirate_boat_cannon_02.png", 10, false, false, 0.1));
	fBoat->AddAnimClip(make_shared<AnimationClip>(L"Attack03", L"_Textures/Pirate/pirate_boat_cannon_03.png", 9, false, false, 0.1));

	// Death


	// bBoat
	// 1Phase Idle
	bBoat->AddAnimClip(make_shared<AnimationClip>(L"Sail", L"_Textures/Pirate/pirate_boatSail.png", 18, false, true, 0.1));

	// fRail
	fRail->AddAnimClip(make_shared<AnimationClip>(L"Rail", L"_Textures/Pirate/pirate_boatRail.png", 3, false, true, 0.1));


	// Components
	captain->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
	fBoat->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
	// AddAnimator
	captain->AddComponent(make_shared<AnimatorComponent>(captain->GetAnimClips()));
	tCaptain->AddComponent(make_shared<AnimatorComponent>(tCaptain->GetAnimClips()));
	fBoat->AddComponent(make_shared<AnimatorComponent>(fBoat->GetAnimClips()));
	fRail->AddComponent(make_shared<AnimatorComponent>(fRail->GetAnimClips()));
	bBoat->AddComponent(make_shared<AnimatorComponent>(bBoat->GetAnimClips()));

	// animRect SetAnimator
	captain->SetAnimator(captain->GET_COMP(Animator));
	tCaptain->SetAnimator(tCaptain->GET_COMP(Animator));
	fBoat->SetAnimator(fBoat->GET_COMP(Animator));
	fRail->SetAnimator(fRail->GET_COMP(Animator));
	bBoat->SetAnimator(bBoat->GET_COMP(Animator));
}

void Pirate::Collision(shared_ptr<Player> player)
{
	// playerBullts&enemies
	for (int i = 0; i < player->GetBullet()->GetBullets().size(); ++i)
	{
		if (player->GetBullet()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(captain->GET_COMP(Collider)))
		{
			if (player->GetBullet()->GetBullets()[i]->GetHit())
			{
				player->GetBullet()->GetBullets()[i]->Hit();
				--hp;
			}
		}
	}

	for (int i = 0; i < player->GetSpecialAttack()->GetBullets().size(); ++i)
	{
		if (player->GetSpecialAttack()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(captain->GET_COMP(Collider)))
			--hp;
	}

	if(player->GetSuperBeam()->GetAnimRect()->GET_COMP(Collider)->Intersect(captain->GET_COMP(Collider)))
		--hp;	

	// playerPos, Bullet Rotation
	if (currentPhase == 1 && cState == PirateState::Attack)
	{
		float distance = (float)sqrt(pow(player->GetAnimRect()->GetPosition().x - captain->GetPosition().x, 2) + pow(player->GetAnimRect()->GetPosition().y - captain->GetPosition().y, 2));

		Vector2 reference = captain->GetPosition();
		Vector2 point = Vector2(player->GetAnimRect()->GetPosition().x, player->GetAnimRect()->GetPosition().y);

		float R = (float)sqrt(pow((point.x - reference.x), 2) + pow((point.y - reference.y), 2));
		bulletRotate = acos((point.x - reference.x) / R);
		bulletRotate = (bulletRotate * 180) / (float)acos(-1);
	}
}

void Pirate::Update()
{
	if (bMod)
	{
		if (!(ImGui::IsAnyItemActive()) && captain->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			captainInfo.position = INPUT->GetMousePosition() - boatInfo.position;
		else if (!(ImGui::IsAnyItemActive()) && fBoat->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
			boatInfo.position = INPUT->GetMousePosition();

		// Init
		captain->SetPosition(boatInfo.position + captainInfo.position * captainInfo.totalSize);
		fBoat->SetPosition(boatInfo.position);
		hp = maxHp;
		phaseIntro = false;
		bIntro = true;
		captainInfo.time = 0.0f;
		boatInfo.time = 0.0f;
	}

	captainInfo.time += DELTA;
	boatInfo.time += DELTA;

	if (bIntro)
		cState = PirateState::Intro;
	else if (captainInfo.time >= captainInfo.delayTime - 6.0f && bWhistle)
		cState = PirateState::Whistle;
	else if (captainInfo.time >= captainInfo.delayTime)
		cState = PirateState::Attack;
	else
		cState = PirateState::Idle;

//	cout << ((int)((float)hp / (float)maxHp * 100)) << '\n';
	if (currentPhase == 1 && (int)((float)hp / (float)maxHp * 100) <= SecPhase + bAttackPer
		&& boatInfo.time >= boatInfo.delayTime)
		bState = PirateState::Attack;
	else
		bState = PirateState::Idle;

	if (currentPhase == 1)
	{
		bBoat->SetPosition(boatInfo.position + Vector2(105, 267) * boatInfo.totalSize);
		bBoat->SetScale(Vector2(529, 412) * 0.8 * boatInfo.totalSize);
		bBoat->GET_COMP(Animator)->SetCurrentAnimClip(L"Sail");
		
		fRail->SetPosition(boatInfo.position + Vector2(100, 134) * boatInfo.totalSize);
		fRail->SetScale(Vector2(164, 80) * 0.8 * boatInfo.totalSize);
		fRail->GET_COMP(Animator)->SetCurrentAnimClip(L"Rail");
	}

	switch (cState)
	{
	case PirateState::None:
		break;
	case PirateState::Idle:
		captain->GET_COMP(Animator)->SetCurrentAnimClip(L"Idle");
		captain->SetScale(Vector2(385, 370) * captainInfo.totalSize);
		captain->SetPosition(boatInfo.position + captainInfo.position * captainInfo.totalSize);
		break;
	case PirateState::Attack:
		if (captainInfo.animClipCount == 0)
		{
			captainInfo.subAnimRect = true;

			captain->GET_COMP(Animator)->SetCurrentAnimClip(L"PShotS");
			captain->SetScale(Vector2(580, 465) * captainInfo.totalSize);
			captain->SetPosition(boatInfo.position + (captainInfo.position + Vector2(35, -10)) * captainInfo.totalSize);

			tCaptain->GET_COMP(Animator)->SetCurrentAnimClip(L"TPShotS");
			tCaptain->SetScale(Vector2(580, 465) * captainInfo.totalSize);
			tCaptain->SetPosition(captain->GetPosition());
			if (captain->GET_COMP(Animator)->GetEnd())
			{
				++captainInfo.animClipCount;
				deltaTime = 0.0f;
				uniform_int_distribution<int> randomCount(2, 4);
				count = randomCount(mt);
			}
		}
		else if (captainInfo.animClipCount <= count && deltaTime >= 2.0f)
		{
			captain->GET_COMP(Animator)->SetCurrentAnimClip(L"PShot");
			captain->SetScale(Vector2(665, 415) * captainInfo.totalSize);
			captain->SetPosition(boatInfo.position + (captainInfo.position + Vector2(80, 25)) * captainInfo.totalSize);
			
			tCaptain->GET_COMP(Animator)->SetCurrentAnimClip(L"TPShot");
			tCaptain->SetScale(Vector2(665, 415) * captainInfo.totalSize);
			tCaptain->SetPosition(captain->GetPosition());

			PEABULLETMANAGER->Init(captain->GetPosition() + Vector2(-283.0f, -115.0f) * captainInfo.totalSize, bulletRotate, 750.0f);
			if (captain->GET_COMP(Animator)->GetCurrentFrameIndex() >= 7 && !check)
			{
				check = true;
				PEABULLETMANAGER->IndexManagement();
			}

			if (captain->GET_COMP(Animator)->GetEnd())
			{
				check = false;
				++captainInfo.animClipCount;
				deltaTime = 0.0f;
			}
		}
		else if (captainInfo.animClipCount <= count)
		{
			deltaTime += DELTA;
			captain->GET_COMP(Animator)->SetCurrentAnimClip(L"PShotI");
			captain->SetScale(Vector2(442, 360) * captainInfo.totalSize);
			captain->SetPosition(boatInfo.position + (captainInfo.position + Vector2(102, 0)) * captainInfo.totalSize);

			tCaptain->GET_COMP(Animator)->SetCurrentAnimClip(L"TPShotI");
			tCaptain->SetScale(Vector2(442, 360)* captainInfo.totalSize);
			tCaptain->SetPosition(captain->GetPosition());
		}
		else
		{
			captain->GET_COMP(Animator)->SetCurrentAnimClip(L"PShotE");
			captain->SetScale(Vector2(490, 465) * captainInfo.totalSize);
			captain->SetPosition(boatInfo.position + (captainInfo.position + Vector2(75, -8)) * captainInfo.totalSize);

			tCaptain->GET_COMP(Animator)->SetCurrentAnimClip(L"TPShotE");
			tCaptain->SetScale(Vector2(490, 465)* captainInfo.totalSize);
			tCaptain->SetPosition(captain->GetPosition());
			if (captain->GET_COMP(Animator)->GetEnd())
			{
				bWhistle = true;
				captainInfo.time = 0.0f;
				captainInfo.animClipCount = 0;

				captainInfo.subAnimRect = false;
			}
		}
		break;
	case PirateState::Whistle:
		if (captainInfo.animClipCount == 0)
		{
			captain->GET_COMP(Animator)->SetCurrentAnimClip(L"Whistle01");
			captain->SetScale(Vector2(630, 485) * captainInfo.totalSize);
			captain->SetPosition(boatInfo.position + (captainInfo.position + Vector2(89, 57)) * captainInfo.totalSize);
			if (captain->GET_COMP(Animator)->GetEnd())
				++captainInfo.animClipCount;
		}
		else if (captainInfo.animClipCount == 1)
		{
			captain->GET_COMP(Animator)->SetCurrentAnimClip(L"Whistle02");
			captain->SetScale(Vector2(630, 485) * captainInfo.totalSize);
			captain->SetPosition(boatInfo.position + (captainInfo.position + Vector2(89, 57)) * captainInfo.totalSize);
			if (captain->GET_COMP(Animator)->GetEnd())
				++captainInfo.animClipCount;
		}
		else if (captainInfo.animClipCount == 2)
		{
			captain->GET_COMP(Animator)->SetCurrentAnimClip(L"Whistle03");
			captain->SetScale(Vector2(630, 485) * captainInfo.totalSize);
			captain->SetPosition(boatInfo.position + (captainInfo.position + Vector2(89, 57)) * captainInfo.totalSize);
			if (captain->GET_COMP(Animator)->GetEnd())
				++captainInfo.animClipCount;
		}
		else if (captainInfo.animClipCount == 3)
		{
			captain->GET_COMP(Animator)->SetCurrentAnimClip(L"Whistle04");
			captain->SetScale(Vector2(630, 485) * captainInfo.totalSize);
			captain->SetPosition(boatInfo.position + (captainInfo.position + Vector2(89, 57)) * captainInfo.totalSize);
			if (captain->GET_COMP(Animator)->GetEnd())
				++captainInfo.animClipCount;
		}
		else
		{
			captain->GET_COMP(Animator)->SetCurrentAnimClip(L"Whistle05");
			captain->SetScale(Vector2(630, 485) * captainInfo.totalSize);
			captain->SetPosition(boatInfo.position + (captainInfo.position + Vector2(89, 57)) * captainInfo.totalSize);
			if (captain->GET_COMP(Animator)->GetEnd())
			{
				captainInfo.animClipCount = 0;
				captainInfo.time = 0;
				bWhistle = false;

			//	SHARK->Init(Vector2(CAMERA->GetPosition().x, 302.0f), 1.0f);
				DOGFISH->Init(boatInfo.position, 1.0f);
			}
		}
		break;
	case PirateState::Intro:
		if (captainInfo.animClipCount == 0)
		{
			captain->GET_COMP(Animator)->SetCurrentAnimClip(L"IntroS");
			captain->SetScale(Vector2(360, 400) * captainInfo.totalSize);
			captain->SetPosition(boatInfo.position + captainInfo.position * captainInfo.totalSize);
			if (captain->GET_COMP(Animator)->GetEnd())
			{
				++captainInfo.animClipCount;
			}
		}
		else if (captainInfo.animClipCount <= 7)
		{
			captain->GET_COMP(Animator)->SetCurrentAnimClip(L"IntroL");
			captain->SetScale(Vector2(360, 400) * captainInfo.totalSize);
			captain->SetPosition(boatInfo.position + captainInfo.position * captainInfo.totalSize);
			if (captain->GET_COMP(Animator)->GetEnd())
			{
				captain->GET_COMP(Animator)->ResetFrame();
				++captainInfo.animClipCount;
			}
		}
		else
		{
			captain->GET_COMP(Animator)->SetCurrentAnimClip(L"IntroE");
			captain->SetScale(Vector2(360, 400) * captainInfo.totalSize);
			captain->SetPosition(boatInfo.position + captainInfo.position * captainInfo.totalSize);
			if (captain->GET_COMP(Animator)->GetEnd())
			{
				captainInfo.animClipCount = 0;
				bIntro = false;
			}
		}
		break;
	}

	switch (bState)
	{
	case PirateState::None:
		break;
	case PirateState::Idle:
		fBoat->GET_COMP(Animator)->SetCurrentAnimClip(L"Idle");
		fBoat->SetScale(Vector2(461, 523) * boatInfo.totalSize);
		fBoat->SetPosition(boatInfo.position);
		break;
	case PirateState::Attack:
		if (boatInfo.animClipCount == 0)
		{
			fBoat->GET_COMP(Animator)->SetCurrentAnimClip(L"Attack01");
			fBoat->SetScale(Vector2(485, 505) * boatInfo.totalSize);
			fBoat->SetPosition(boatInfo.position + Vector2(8, 11) * boatInfo.totalSize);
			if (fBoat->GET_COMP(Animator)->GetEnd())
				++boatInfo.animClipCount;
		}
		else if (boatInfo.animClipCount == 1)
		{
			fBoat->GET_COMP(Animator)->SetCurrentAnimClip(L"Attack02");
			fBoat->SetScale(Vector2(485, 505) * boatInfo.totalSize);
			fBoat->SetPosition(boatInfo.position + Vector2(8, 11) * boatInfo.totalSize);
			CANNONBALLMANAGER->Init(fBoat->GetPosition() + Vector2(-150.0f, -80.0f) * boatInfo.totalSize, 0.0f, 750.0f);
			if (fBoat->GET_COMP(Animator)->GetEnd())
			{
				++boatInfo.animClipCount;
				// Bullet ȣ��
				CANNONBALLMANAGER->IndexManagement();
			}
		}
		else
		{
			fBoat->GET_COMP(Animator)->SetCurrentAnimClip(L"Attack03");
			fBoat->SetScale(Vector2(485, 505) * boatInfo.totalSize);
			fBoat->SetPosition(boatInfo.position + Vector2(8, 11) * boatInfo.totalSize);
			if (fBoat->GET_COMP(Animator)->GetEnd())
			{
				boatInfo.animClipCount = 0;
				boatInfo.time = 0.0f;
			}
		}
		break;
	case PirateState::Start2P:
		break;
	case PirateState::Death:
		break;
	}

	if (!captainInfo.subAnimRect)
		tCaptain->SetPosition(Vector2(1000, -1000));

	if (direction)	// ��
	{
		speed += DELTA / 2.5;
		if (speed >= waveValue)
			direction = false;
	}
	else	// ��
	{
		speed -= DELTA / 2.5;
		if (speed <= -waveValue)
			direction = true;
	}
	boatInfo.position.y += speed;

	PEABULLETMANAGER->SetTotalSize(captainInfo.totalSize);
	CANNONBALLMANAGER->SetTotalSize(captainInfo.totalSize);
	CANNONBALLMANAGER->Update();
	PEABULLETMANAGER->Update();
	SHARK->Update();
	DOGFISH->Update();
	bBoat->Update();
	captain->Update();
	fRail->Update();
	fBoat->Update();
	tCaptain->Update();
}

void Pirate::Render()
{
	bBoat->Render();
	PEABULLETMANAGER->Render();
	captain->Render();
	CANNONBALLMANAGER->Render();
	fRail->Render();
	fBoat->Render();
	if (captainInfo.subAnimRect)
		tCaptain->Render();
}

void Pirate::GUI()
{
	static bool bOpen = true;
	if (ImGui::Begin("Pirate", &bOpen))
	{
		ImGui::InputInt("MaxHp", (int*)&maxHp);
		ImGui::SliderFloat("SecondPhase", &SecPhase, 10.0f, 90.0f, "%.0f");
		float tempWave = waveValue;
		if (ImGui::InputFloat("WaveValue", &tempWave, 0.1f, 10.0f, "%.2f"))
		{
			direction = true;
			waveValue = tempWave;
			speed = waveValue / 2;
			boatInfo.position.y = defPos.y;
		}
		
		string text = "Captain";
		ImGui::Text(text.c_str());
		ImGui::InputFloat("AddPos.x", (float*)&captainInfo.position.x, 1.0f, 100.0f);
		ImGui::InputFloat("AddPos.y", (float*)&captainInfo.position.y, 1.0f, 100.0f);
		ImGui::InputFloat("CScale", &captainInfo.totalSize, 0.1f, 10.0f, "%0.2f");
		ImGui::InputFloat("CDelay", &captainInfo.delayTime);
	
		text = "Boat";
		ImGui::Text(text.c_str());
		if (ImGui::SliderFloat2("Position", (float*)&defPos, CAMERA->GetPosition().x, CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH))
		{
			direction = true;
			speed = waveValue / 2;
			boatInfo.position.y = defPos.y;
		}
		ImGui::InputFloat("BScale", &boatInfo.totalSize, 0.1f, 10.0f, "%0.2f");
		ImGui::InputFloat("BDelay", &boatInfo.delayTime);
		ImGui::SliderFloat("BoatAttackPercent", &bAttackPer, 10.0f, (100.0f - SecPhase) - 10.0f, "%.0f");
	}
	ImGui::End();
}