#include "stdafx.h"
#include "CroaksPBison.h"

CroaksPBison::CroaksPBison()
{
	// 초기화
	animRect = make_shared<AnimationRect>(CENTER, Vector2(243, 144), 0.0f, L"_Textures/RibbyCroaks/tallfrog_slotman_platform_bison.png");
	topAnimRect = make_shared<AnimationRect>(CENTER, Vector2(243, 144), 0.0f, L"_Textures/RibbyCroaks/tallfrog_slotman_platform_bison_top.png");

	flameRect = make_shared<AnimationRect>(CENTER, Vector2(60, 90), 0.0f, L"_Textures/RibbyCroaks/tallfrog_slotman_platform_bison_flame_sm.png");

	collisionRect = make_shared<ColorRect>(Vector2(animRect->GetPosition().x, animRect->GetPosition().y), Vector2(197, 110), 0.0f, BLACK);

	// Idle
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Idle", L"_Textures/RibbyCroaks/tallfrog_slotman_platform_bison.png", 10, false, true, 0.1));
	topAnimRect->AddAnimClip(make_shared<AnimationClip>(L"Idle", L"_Textures/RibbyCroaks/tallfrog_slotman_platform_bison_top.png", 10, false, true, 0.1));

	flameRect->AddAnimClip(make_shared<AnimationClip>(L"FlameSm", L"_Textures/RibbyCroaks/tallfrog_slotman_platform_bison_flame_sm.png", 6, false, true, 0.1));
	flameRect->AddAnimClip(make_shared<AnimationClip>(L"FlameLgS", L"_Textures/RibbyCroaks/tallfrog_slotman_platform_bison_flame_lg_start.png", 4, false, false, 0.1));
	flameRect->AddAnimClip(make_shared<AnimationClip>(L"FlameLgL", L"_Textures/RibbyCroaks/tallfrog_slotman_platform_bison_flame_lg_loop.png", 6, false, true, 0.1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	topAnimRect->AddComponent(make_shared<AnimatorComponent>(topAnimRect->GetAnimClips()));

	flameRect->AddComponent(make_shared<AnimatorComponent>(flameRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));
	topAnimRect->SetAnimator(topAnimRect->GET_COMP(Animator));

	flameRect->SetAnimator(flameRect->GET_COMP(Animator));

	// Components
	collisionRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
	flameRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));

	// radom
	random_device random;
	mt = mt19937(random());

	SOUND->AddSound("BBurst", L"_Sounds/sfx_frogs_flame_platform_fire_burst_01.wav", false, true);
}

void CroaksPBison::Collision(shared_ptr<Player> player)
{
	if (collisionRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= PlayerState::Special_Attack_R && player->GetState() <= PlayerState::Super_Beam_L))
	{
		// 충돌시 player가 object 위인 경우
		if (player->GetAnimRect()->GetPosition().y > collisionRect->GetPosition().y + collisionRect->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().x > collisionRect->GetPosition().x - collisionRect->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().x < collisionRect->GetPosition().x + collisionRect->GetScale().x / 2)
		{
			player->SetCheckCollider(true);

			// player move
			if (player->GetAnimRect()->GetPosition().x - player->GetAnimRect()->GetScale().x * 0.5f > CAMERA->GetPosition().x)
				player->GetAnimRect()->Move(Vector2(-speed, 0));

			player->SetGroundPos(Vector2(collisionRect->GetPosition().x, collisionRect->GetPosition().y + collisionRect->GetScale().y / 2));

		//	cout << "Up\n";
		}	// 충돌시 player가 object 옆인 경우
		else
			player->SetHit(true);

	}

	if (flameRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= PlayerState::Special_Attack_R && player->GetState() <= PlayerState::Super_Beam_L))
		player->SetHit(true);
		
}

void CroaksPBison::GroundCollision()
{
	if ((animRect->GetPosition().y - animRect->GetScale().y * 0.5f) >= groundY)
	{
		bGround = true;
		animRect->SetPosition(Vector2(animRect->GetPosition().x, groundY + animRect->GetScale().y * 0.5f));
	}
	else
		bGround = false;

	if (vel < 0.0f)
		bGround = false;
}

void CroaksPBison::Init(Vector2 position, float groundY)
{
	vel = 0.0f;
	bLoop = false;
	time = 0.0f;
	bActivation = true;
	bBurstS = false;

	animRect->SetPosition(position);
	topAnimRect->SetPosition(animRect->GetPosition());
	flameRect->SetPosition(animRect->GetPosition());
	this->groundY = groundY;

	uniform_int_distribution<int> randomSize(0, 1);
	direction = randomSize(mt);
}

void CroaksPBison::Update()
{
	if (bActivation)
	{
		time += DELTA;
		GroundCollision();

		if (!bGround)
			vel += G * 200 * DELTA;
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Idle");
		topAnimRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Idle");

		coef_res = 0.5f;
		if (bGround)
		{
			vel *= -1.0f * coef_res;
			bGround = false;
		}
		animRect->Move(Vector2(-speed, vel));

		if (time >= flameTime)
		{
			flameRect->SetScale(Vector2(95, 704) * totalSize);
			if (!bLoop)
			{
				if (!bBurstS)
				{
					bBurstS = true;
					SOUND->Play("BBurst");
				}
				flameRect->GET_COMP(Animator)->SetCurrentAnimClip(L"FlameLgS");
				if (flameRect->GET_COMP(Animator)->GetEnd())
					bLoop = true;
			}
			else
				flameRect->GET_COMP(Animator)->SetCurrentAnimClip(L"FlameLgL");

			if (direction)
			{
				flameRect->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y + flameRect->GetScale().y * 0.5f + 30));
				flameRect->SetRotation(0.0f);
			}
			else
			{
				flameRect->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y - flameRect->GetScale().y * 0.5f - 40));
				flameRect->SetRotation(180.0f);
			}
		}
		else
		{
			flameRect->SetScale(Vector2(60, 90) * totalSize);
			flameRect->GET_COMP(Animator)->SetCurrentAnimClip(L"FlameSm");
			if (direction)
			{
				flameRect->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y + flameRect->GetScale().y * 0.5f + 30));
				flameRect->SetRotation(0.0f);
			}
			else
			{
				flameRect->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y - flameRect->GetScale().y * 0.5f - 40));
				flameRect->SetRotation(180.0f);
			}
		}
	}

	if (bActivation == true)
	{
		// End
		if (animRect->GetPosition().y > CAMERA->GetPosition().y + WIN_DEFAULT_HEIGHT + 200 || animRect->GetPosition().y < CAMERA->GetPosition().y - 200
			|| animRect->GetPosition().x > CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH + 200 || animRect->GetPosition().x < CAMERA->GetPosition().x - 200)
			bActivation = false;
	}
	else
		animRect->SetPosition(Vector2(1000, -1000));

	// collisionRect update
	collisionRect->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y));
	topAnimRect->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y));
	flameRect->SetPosition(Vector2(animRect->GetPosition().x, flameRect->GetPosition().y));

	animRect->SetScale(Vector2(243, 144) * totalSize);
	topAnimRect->SetScale(Vector2(243, 144) * totalSize);
	collisionRect->SetScale(Vector2(197, 110) * totalSize);

	animRect->Update();
	topAnimRect->Update();
	flameRect->Update();
	collisionRect->Update();
}

void CroaksPBison::Render()
{
	animRect->Render();
	flameRect->Render();
	topAnimRect->Render();

//	collisionRect->Render();
}
