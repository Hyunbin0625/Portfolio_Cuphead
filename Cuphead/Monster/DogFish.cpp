#include "stdafx.h"
#include "DogFish.h"

DogFish::DogFish()
{
	animRect = make_shared<AnimationRect>(Vector2(1000, -1000), Vector2(716, 453), 0.0f, L"_Textures/Pirate/pirate_fish_up.png");
//	dust = make_shared<AnimationRect>(Vector2(1000, -1000), Vector2(178, 156), 0.0f, L"_Textures/Pirate/pirateDogFish_splash.png");

	// Up
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Up", L"_Textures/Pirate/pirate_fish_up.png", 13, false, false, 0.12f));

	// Jump
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Jump01", L"_Textures/Pirate/pirate_fish_jump01.png", 5, false, false, 0.12f));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Jump02", L"_Textures/Pirate/pirate_fish_jump02.png", 5, false, false, 0.12f));

	// Slide
	animRect->AddAnimClip(make_shared<AnimationClip>(L"Slide", L"_Textures/Pirate/pirate_fish_slide.png", 11, false, true, 0.12f));

	// Death
//	animRect->AddAnimClip(make_shared<AnimationClip>(L"Slide", L"_Textures/Pirate/pirate_fish_slide.png", 11, false, true, 0.12f));

	// Dust
//	dust->AddAnimClip(make_shared<AnimationClip>(L"Dust", L"_Textures/Pirate/pirateDogFish_splash.png", 22, false, false, 0.1f));

	animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
	animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));	
//	dust->AddComponent(make_shared<AnimatorComponent>(dust->GetAnimClips()));

	animRect->SetAnimator(animRect->GET_COMP(Animator));
//	dust->SetAnimator(dust->GET_COMP(Animator));
}

void DogFish::Collision(shared_ptr<Player> player)
{
	if (animRect->GET_COMP(Collider)->Intersect(player->GetAnimRect()->GET_COMP(Collider)))
		player->SetHit(true);
}

void DogFish::Init(Vector2 position, float size)
{
	bActivation = true;
	state = DogFishState::Up;
	this->position = position;
	this->totalSize = size;
}

void DogFish::Update()
{
	switch (state)
	{
	case DogFishState::None:
		position = Vector2(1000, -1000);
		animRect->SetPosition(position);
	//	dust->SetPosition(position);
		break;
	case DogFishState::Up:
		break;
	case DogFishState::Jump:
		break;
	case DogFishState::Slide:
		break;
	case DogFishState::Death:
		break;
	}

	if (animRect->GetPosition().x + animRect->GetScale().x <= CAMERA->GetPosition().x)
		state = DogFishState::None;

//	dust->Update();
	animRect->Update();
}

void DogFish::Render()
{
	if (state != DogFishState::None)
	{
		animRect->Render();
	//	dust->Render();
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
	this->position = position;
	this->totalSize = size;
	animRect->SetPosition(Vector2(position.x - 160.0f * totalSize, CAMERA->GetPosition().y + animRect->GetScale().y));
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
			}
		}
		else
		{
		//	time += DELTA;
		//	if (time >= delayTime)
		//	{
		//		dogFishList[currentIndex++]->Init(position, totalSize);
		//
		//		if (currentIndex >= dogFishList.size())
		//		{
		//			if (dogFishList[0]->GetState() == 0)
		//				currentIndex = 0;
		//			else
		//				Create();
		//		}
		//	}
		}
	}

//	for (auto& dogFish : dogFishList)
//		dogFish->Update();
	animRect->Update();
}

void DogFishManager::Render()
{
	if (count <= 1 && bActivation)
	{
		animRect->Render();
		cout << "true\n";
	}
	else if (bActivation)
	{
//		for (auto& dogFish : dogFishList)
//			dogFish->Render();
	}
}

void DogFishManager::GUI()
{
	string objName = "DogFish";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		animRect->SetOutline(true);

		if (ImGui::InputFloat("Pos.x", (float*)&position.x, 1.0f, 100.0f))
			animRect->SetPosition(position);
		if (ImGui::InputFloat("Pos.y", (float*)&position.y, 1.0f, 100.0f))
			animRect->SetPosition(position);
		ImGui::InputFloat("Scale", &totalSize, 0.1f, 10.0f, "%0.2f");

		ImGui::InputFloat("Speed", &speed, 1.0f, 1000.0f, "%0.2f");
		float tempJumpS = dogFishList[0]->GetJumpSpeed();
		if (ImGui::InputFloat("JumpSpeed", &tempJumpS, 0.1f, 100.0f, "%0.2f"))
		{
			for (auto& dogFish : dogFishList)
				dogFish->SetJumpSpeed(tempJumpS);
		}
		float tempAclrt = dogFishList[0]->GetAclrt();
		if (ImGui::InputFloat("Acceleration", &tempAclrt, 0.1f, 100.0f, "%0.2f"))
		{
			for (auto& dogFish : dogFishList)
				dogFish->SetAclrt(tempAclrt);
		}

		ImGui::InputFloat("DelayTime", &delayTime, 0.1f, 10.0f);

		ImGui::EndMenu();
	}
	else
	{
		animRect->SetOutline(false);
	}
}
