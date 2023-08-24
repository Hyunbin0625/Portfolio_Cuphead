#include "stdafx.h"
#include "DogFish.h"

DogFish::DogFish()
{
	animRect = make_shared<AnimationRect>(Vector2(1000, -1000), Vector2(192, 246), 0.0f, L"_Textures/Pirate/pirate_fish_up.png");
	dust = make_shared<AnimationRect>(Vector2(1000, -1000), Vector2(178, 156), 0.0f, L"_Textures/Pirate/pirate_fish_splash.png");

	// Up
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Up", L"_Textures/Pirate/pirate_fish_up.png", 13, false, false, 0.12f));

	// Jump
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Jump01", L"_Textures/Pirate/pirate_fish_jump01.png", 5, false, false, 0.12f));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Jump02", L"_Textures/Pirate/pirate_fish_jump02.png", 5, false, false, 0.12f));

	// Slide
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Slide", L"_Textures/Pirate/pirate_fish_slide.png", 11, false, true, 0.12f));

	// Death
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Death", L"_Textures/Pirate/pirate_fish_death.png", 8, false, true, 0.12f));

	// Dust
	dust->AddAnimClip(make_shared<AnimationClip>(L"Splash", L"_Textures/Pirate/pirate_fish_splash.png", 11, false, false, 0.12f));
	dust->AddAnimClip(make_shared<AnimationClip>(L"Explode", L"_Textures/Pirate/pirate_fish_explode.png", 10, false, false, 0.12f));

	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));	
	dust->AddComponent(make_shared<AnimatorComponent>(dust->GetAnimClips()));

	animRect->SetAnimator(animRect->GET_COMP(Animator));
	dust->SetAnimator(dust->GET_COMP(Animator));
}

void DogFish::Collision(shared_ptr<Player> player)
{
	// player
	if (state != DogFishState::Death
		&& animRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
		player->SetHit(true);

	// playerBullts&enemies Collision
	for (int i = 0; i < player->GetBullet()->GetBullets().size(); ++i)
	{
		if (player->GetBullet()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(animRect->GET_COMP(Collider)) && state != DogFishState::Death)
		{
			--hp;
			player->GetBullet()->GetBullets()[i]->SetActivation(false);
		}
	}

	for (int i = 0; i < player->GetSpecialAttack()->GetBullets().size(); ++i)
	{
		if (player->GetSpecialAttack()->GetBullets()[i]->GetAnimRect()->GET_COMP(Collider)->Intersect(animRect->GET_COMP(Collider)) && state != DogFishState::Death)
			--hp;
	}

	if (player->GetSuperBeam()->GetAnimRect()->GET_COMP(Collider)->Intersect(animRect->GET_COMP(Collider)) && state != DogFishState::Death)
		--hp;
}

void DogFish::Init(Vector2 position, float size, float speed, int maxHp)
{
	this->position = Vector2(position.x + 100.0f, CAMERA->GetPosition().y - animRect->GetScale().y * 0.5f);
	this->totalSize = size;
	this->speed = speed;
	this->hp = maxHp;
	
	val = 0.0f;
	bActivation = true;
	state = DogFishState::Up;

	jumpSpeed = maxJumpSpeed;
	animRect->SetPosition(this->position);
	animRect->GET_COMP(Animator)->ResetFrame();
	dust->GET_COMP(Animator)->ResetFrame();
}

void DogFish::Update()
{
	if (state != DogFishState::None
		&& hp <= 0)
		state = DogFishState::Death;

	switch (state)
	{
	case DogFishState::None:
		position = Vector2(1000, -1000);
		animRect->SetPosition(position);
		dust->SetPosition(position);
		break;
	case DogFishState::Up:
		val += G * aclrt * DELTA;
		jumpSpeed -= val;
		animRect->SetScale(Vector2(246, 305) * totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Up");

		dust->SetScale(Vector2(326, 351) * totalSize);
		dust->SetPosition(Vector2(position.x - 140.0f * totalSize, (CAMERA->GetPosition().y + dust->GetScale().y * 0.5f) - 35.0f * totalSize));
		dust->GET_COMP(Animator)->SetCurrentAnimClip(L"Splash");

		animRect->Move(Vector2(-speed, jumpSpeed));
		if (animRect->GetPosition().y - animRect->GetScale().y * 0.5f <= groundPosY - 74.0f
			&& !groundPosY == 0 && jumpSpeed < 0.0f)
		{
			state = DogFishState::Jump;
			val = 0.0f;
		}
		break;
	case DogFishState::Jump:
		if (animCount == 0)
		{
			animRect->SetScale(Vector2(214, 153) * totalSize);
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Jump01");

			if (animRect->GET_COMP(Animator)->GetCurrentFrameIndex() >= 2)
				animRect->Move(Vector2(-speed * 1.5f, 0));

			if (animRect->GET_COMP(Animator)->GetEnd())
			{
				animRect->SetPosition(animRect->GetPosition() + Vector2(0, -10) * totalSize);
				++animCount;
			}
		}
		else if (animCount == 1)
		{
			animRect->SetScale(Vector2(215, 120) * totalSize);
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Jump02");

			if (animRect->GET_COMP(Animator)->GetCurrentFrameIndex() >= 2)
				animRect->Move(Vector2(-speed * 1.5f, 0));

			if (animRect->GET_COMP(Animator)->GetEnd())
			{
				animCount = 0;
				state = DogFishState::Slide;
				animRect->SetPosition(animRect->GetPosition() + Vector2(0, -20) * totalSize);
			}
		}
		break;
	case DogFishState::Slide:
		animRect->SetScale(Vector2(243, 102) * totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Slide");
		animRect->Move(Vector2(-speed, 0));
		break;
	case DogFishState::Death:
		animRect->SetScale(Vector2(250, 118) * totalSize);
		animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Death");
		animRect->Move(Vector2(0, speed));
		
		if (animCount == 0)	// 한번만 set하기 위해, animCount 재활용
		{
			dust->SetPosition(animRect->GetPosition() + Vector2(0, 50) * totalSize);
			++animCount;
		}
		dust->SetScale(Vector2(278, 297) * totalSize);
		dust->GET_COMP(Animator)->SetCurrentAnimClip(L"Explode");
		break;
	}

	if (animRect->GetPosition().x + animRect->GetScale().x <= CAMERA->GetPosition().x
		|| animRect->GetPosition().y - animRect->GetScale().y >= CAMERA->GetPosition().y + WIN_DEFAULT_HEIGHT)
	{
		state = DogFishState::None;
		animCount = 0;
	}

	if (dust->GET_COMP(Animator)->GetEnd())
		dust->SetPosition(Vector2(1000, -1000));

	dust->Update();
	animRect->Update();
}

void DogFish::Render()
{
	if (state != DogFishState::None)
	{
		animRect->Render();
		dust->Render();
	}
}

// DogFishManager class
DogFishManager::DogFishManager()
{
	animRect = make_shared<AnimationRect>(Vector2(1000, -1000), Vector2(192, 246), 0.0f, L"_Textures/Pirate/dogfish_periscope_01.png");

	// Intro
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Intro01", L"_Textures/Pirate/dogfish_periscope_01.png", 25, false, false, 0.12f));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Intro02", L"_Textures/Pirate/dogfish_periscope_02.png", 25, false, false, 0.12f));

	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));

	animRect->SetAnimator(animRect->GET_COMP(Animator));

	dogFishList.resize(2);
	for (auto& dogFish : dogFishList)
		dogFish = make_shared<DogFish>();

	random_device random;
	mt = mt19937(random());
}

DogFishManager::~DogFishManager() {}

void DogFishManager::Collision(shared_ptr<Player> player)
{
	for (auto& dogFish : dogFishList)
	{
		if (dogFish->GetState() != 0)
			dogFish->Collision(player);
	}
}

void DogFishManager::Create()
{
	dogFishList.resize(dogFishList.size() * 2);

	for (int i = dogFishList.size() / 2; i < dogFishList.size(); ++i)
		dogFishList[i] = make_shared<DogFish>();
}

void DogFishManager::Init(Vector2 position, float size)
{
	bActivation = true;
	count = 0;
	maxCount = 2;
	this->position = position;
	this->totalSize = size;
	animRect->SetPosition(Vector2(position.x - 120.0f * totalSize, CAMERA->GetPosition().y + animRect->GetScale().y * 0.5f));
	animRect->GET_COMP(Animator)->ResetFrame();
}

void DogFishManager::Update()
{
	if (bActivation)
	{
		if (count == 0)
		{
			animRect->SetScale(Vector2(192, 246) * totalSize);
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Intro01");
			if (animRect->GET_COMP(Animator)->GetEnd())
				++count;
		}
		else if (count == 1)
		{
			animRect->SetScale(Vector2(192, 246) * totalSize);
			animRect->GET_COMP(Animator)->SetCurrentAnimClip(L"Intro02");
			if (animRect->GET_COMP(Animator)->GetEnd())
			{
				++count;
				uniform_int_distribution<int> random(3, 5);
				animRect->SetPosition(Vector2(1000, -1000));

				maxCount += random(mt);
			}
		}
		else if (count < maxCount)
		{
			time += DELTA;
			if (time >= delayTime)
			{
				time = 0.0f;
				dogFishList[currentIndex++]->Init(position, totalSize, speed, hp);

				if (currentIndex >= dogFishList.size())
				{
					if (dogFishList[0]->GetState() == 0)
						currentIndex = 0;
					else
						Create();
				}
				++count;
			}
		}
		else
			bActivation = false;
	}

	for (auto& dogFish : dogFishList)
		dogFish->Update();
	animRect->Update();
}

void DogFishManager::Render()
{
	if (count <= 1 && bActivation)
	{
		animRect->Render();
	}
	for (auto& dogFish : dogFishList)
		dogFish->Render();
}

void DogFishManager::GUI()
{
	string objName = "DogFish";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		animRect->SetOutline(true);

		ImGui::InputInt("MaxHp", &hp);
		if (ImGui::InputFloat("Pos.x", (float*)&position.x, 1.0f, 100.0f))
			animRect->SetPosition(position);
		if (ImGui::InputFloat("Pos.y", (float*)&position.y, 1.0f, 100.0f))
			animRect->SetPosition(position);
		ImGui::InputFloat("Scale", &totalSize, 0.1f, 10.0f, "%0.2f");
		ImGui::InputFloat("Speed", &speed, 1.0f, 1000.0f, "%0.2f");

		ImGui::InputFloat("DelayTime", &delayTime, 0.1f, 10.0f);

		ImGui::EndMenu();
	}
	else
	{
		animRect->SetOutline(false);
	}
}
