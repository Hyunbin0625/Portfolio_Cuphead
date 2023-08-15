#include "stdafx.h"
#include "CroaksPSnake.h"

CroaksPSnake::CroaksPSnake()
{
	// 초기화
	animRect = make_shared<AnimationRect>(CENTER, Vector2(242, 141), 0.0f, L"_Textures/RibbyCroaks/tallfrog_slotman_platform_snake.png");
	collisionRect = make_shared<ColorRect>(Vector2(animRect->GetPosition().x, animRect->GetPosition().y), Vector2(200, 100), 0.0f, BLACK);
	// Idle
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Idle", L"_Textures/RibbyCroaks/tallfrog_slotman_platform_snake.png", 10, false, true, 0.1));

	// AddAnimator
	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	// animRect SetAnimator
	animRect->SetAnimator(animRect->GET_COMP(Animator));

	// Components
	collisionRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void CroaksPSnake::Collision(shared_ptr<Player> player)
{
	if (collisionRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)) && !(player->GetState() >= PlayerState::Special_Attack_R && player->GetState() <= PlayerState::Super_Beam_L))
	{
		// 충돌시 player가 object 위인 경우
		if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 <= collisionRect->GetPosition().y + collisionRect->GetScale().y / 2
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
//		else if (player->GetAnimRect()->GetPosition().y - player->GetAnimRect()->GetScale().y / 2 < collisionRect->GetPosition().y + collisionRect->GetScale().y / 2
//			|| player->GetAnimRect()->GetPosition().y + player->GetAnimRect()->GetScale().y / 2 < collisionRect->GetPosition().y - collisionRect->GetScale().y / 2)
//		{
//			if (player->GetAnimRect()->GetPosition().x + player->GetAnimRect()->GetScale().x / 2 > collisionRect->GetPosition().x - collisionRect->GetScale().x / 2
//				&& player->GetAnimRect()->GetPosition().x < collisionRect->GetPosition().x)
//			{
//				// player hit
//				player->SetHit(true);
//			}
//			if (player->GetAnimRect()->GetPosition().x - player->GetAnimRect()->GetScale().x / 2 < collisionRect->GetPosition().x + collisionRect->GetScale().x / 2
//				&& player->GetAnimRect()->GetPosition().x > collisionRect->GetPosition().x)
//			{
//				// player hit
//				player->SetHit(true);
//			}
//		//	cout << "LeftRight\n";
//		}
	}
}

void CroaksPSnake::GroundCollision()
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

void CroaksPSnake::Init(Vector2 position, float groundY)
{
	vel = 0.0f;
	bActivation = true;
	animRect->SetPosition(position);
	this->groundY = groundY;
}

void CroaksPSnake::Update()
{
	if (bActivation)
	{
		GroundCollision();

		if (!bGround)
			vel += G * 200 * DELTA;
		animRect->SetScale(Vector2(242, 141) * totalSize);
		collisionRect->SetScale(Vector2(200, 100) * totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Idle");

		coef_res = 0.5f;
		if (bGround)
		{
			vel *= -1.0f * coef_res;
			bGround = false;
		}
		animRect->Move(Vector2(-speed, -vel));
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

	// collisionRect position update
	collisionRect->SetPosition(Vector2(animRect->GetPosition().x, animRect->GetPosition().y));

	animRect->Update();
	collisionRect->Update();
}

void CroaksPSnake::Render()
{
	animRect->Render();

//	collisionRect->Render();
}
