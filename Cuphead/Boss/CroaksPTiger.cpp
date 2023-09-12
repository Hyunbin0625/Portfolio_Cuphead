#include "stdafx.h"
#include "CroaksPTiger.h"

CroaksPTiger::CroaksPTiger()
{
	// 초기화
	animRect = make_shared<AnimationRect>(CENTER, Vector2(241, 142), 0.0f, L"_Textures/RibbyCroaks/tallfrog_slotman_platform_tiger.png");
	topAnimRect = make_shared<AnimationRect>(CENTER, Vector2(241, 142), 0.0f, L"_Textures/RibbyCroaks/tallfrog_slotman_platform_tiger_top.png");

	bulletRect = make_shared<AnimationRect>(CENTER, Vector2(97, 90), 0.0f, L"_Textures/RibbyCroaks/tallfrog_slotman_platform_tiger_bullet.png");

	collisionRect = make_shared<ColorRect>(Vector2(animRect->GetPosition().x, animRect->GetPosition().y), Vector2(196, 110), 0.0f, BLACK);

	// Idle
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Idle", L"_Textures/RibbyCroaks/tallfrog_slotman_platform_tiger.png", 10, false, true, 0.1));
	topAnimRect->AddAnimClip(make_shared<AnimationClip>(L"Idle", L"_Textures/RibbyCroaks/tallfrog_slotman_platform_tiger_top.png", 10, false, true, 0.1));

	bulletRect->AddAnimClip(make_shared<AnimationClip>(L"Idle", L"_Textures/RibbyCroaks/tallfrog_slotman_platform_tiger_bullet.png", 3, false, true, 0.1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	topAnimRect->AddComponent(make_shared<AnimatorComponent>(topAnimRect->GetAnimClips()));

	bulletRect->AddComponent(make_shared<AnimatorComponent>(bulletRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));
	topAnimRect->SetAnimator(topAnimRect->GET_COMP(Animator));

	bulletRect->SetAnimator(bulletRect->GET_COMP(Animator));

	// Components
	collisionRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
	bulletRect->AddComponent(make_shared<ColliderComponent>(ColliderType::CIRCLE));
}

void CroaksPTiger::Collision(shared_ptr<Player> player)
{
	if (collisionRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= PlayerState::Special_Attack_R && player->GetState() <= PlayerState::Super_Beam_L))
	{
		// 충돌시 player가 object 위인 경우
		if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 + 3>= collisionRect->GetPosition().y + collisionRect->GetScale().y / 2
			&& player->GetAnimRect()->GetPosition().x > collisionRect->GetPosition().x - collisionRect->GetScale().x / 2
			&& player->GetAnimRect()->GetPosition().x < collisionRect->GetPosition().x + collisionRect->GetScale().x / 2)
		{
			player->SetCheckCollider(true);

			// player move
			player->GetAnimRect()->Move(Vector2(-speed, 0));

			player->SetGroundPos(Vector2(collisionRect->GetPosition().x, collisionRect->GetPosition().y + collisionRect->GetScale().y / 2));

			if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < collisionRect->GetPosition().y + collisionRect->GetScale().y / 2 - 1)
				player->GetAnimRect()->Move(Vector2(0, 400));
			
		//	cout << "Up\n";
		}	// 충돌시 player가 object 옆인 경우
		else
			player->SetHit(true);
	}

	if (bulletRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= PlayerState::Special_Attack_R && player->GetState() <= PlayerState::Super_Beam_L))
		player->SetHit(true);
		
}

void CroaksPTiger::GroundCollision()
{
	if ((animRect->GetPosition().y - animRect->GetScale().y * 0.5f) <= groundY)
	{
		bGround = true;
		animRect->SetPosition(Vector2(animRect->GetPosition().x, groundY + animRect->GetScale().y * 0.5f));
	}
	else
		bGround = false;

	if (vel < 0.0f)
		bGround = false;
}

void CroaksPTiger::Init(Vector2 position, float groundY)
{
	vel = 0.0f;
	BVel = 0.0f;
	bActivation = true;
	bBallS = false;

	animRect->SetPosition(position);
	topAnimRect->SetPosition(animRect->GetPosition());
	bulletRect->SetPosition(animRect->GetPosition());
	this->groundY = groundY;
}

void CroaksPTiger::Update()
{
	if (bActivation)
	{
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
		animRect->Move(Vector2(-speed, -vel));

		bulletRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Idle");
		if (bulletRect->GetPosition().y <= animRect->GetPosition().y)
		{
			if(!bBallS)
			{
				bBallS = true;
				SOUND->Play("BBall");
			}
			BVel = maxJumpSpeed;
		}
		else
			BVel -= G * 200 * DELTA;
		bulletRect->Move(Vector2(0, BVel));
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
	bulletRect->SetPosition(Vector2(animRect->GetPosition().x, bulletRect->GetPosition().y));

	animRect->SetScale(Vector2(241, 142) * totalSize);
	topAnimRect->SetScale(Vector2(241, 142) * totalSize);
	collisionRect->SetScale(Vector2(196, 110) * totalSize);

	bulletRect->SetScale(Vector2(97, 90) * totalSize);

	animRect->Update();
	topAnimRect->Update();
	bulletRect->Update();
	collisionRect->Update();
}

void CroaksPTiger::Render()
{
	animRect->Render();
	bulletRect->Render();
	topAnimRect->Render();

	//	collisionRect->Render();
}
