#include "stdafx.h"
#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(UINT totalBullet, float bulletSpeed, float speakerSpeed, const wstring& texturePath)
	: Bullet(totalBullet, bulletSpeed, speakerSpeed), texturePath(texturePath)
{
	for (auto& animRect : animRects)
		animRect = make_shared<AnimationRect>(Vector2(), Vector2(159, 43), 0.0f, texturePath);

	for (auto& animRect : animRects)
		animRect->AddAnimClip(make_shared<AnimationClip>(L"PeaShot", texturePath, 6, false, true, 0.1));

	for (auto& animRect : animRects)
	{
		animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
		animRect->SetAnimator(animRect->GET_COMP(Animator));
	}

	for (auto active : activation)
		active = 0;

	// AddComponent
	for (auto& animRect : animRects)
		animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
}

void PlayerBullet::CreateBullet()
{
	vector<shared_ptr<AnimationRect>> tempAnimRects;
	vector<bool> tempActivation;
	tempAnimRects.assign(totalBullet * 2, make_shared<AnimationRect>());
	tempActivation.assign(totalBullet * 2, bool());
	for (int i = 0; i < (int)totalBullet; ++i)
	{
		tempAnimRects[i] = animRects[i];
		tempActivation[i] = activation[i];
	}

	totalBullet *= 2;
	animRects.assign(totalBullet, make_shared<AnimationRect>());
	activation.assign(totalBullet, bool());

	for (int i = 0; i < (int)totalBullet; ++i)
	{
		animRects[i] = tempAnimRects[i];
		activation[i] = tempActivation[i];
	}

	for (int i = totalBullet / 2; i < (int)totalBullet; ++i)
		animRects[i] = make_shared<AnimationRect>(Vector2(-500, -500), Vector2(159, 43), 0.0f, texturePath);

	// AddComponent
	for (auto& animRect : animRects)
	{
		animRect->AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
		animRect->AddAnimClip(make_shared<AnimationClip>(L"PeaShot", texturePath, 6, false, true, 0.1));
		animRect->AddComponent(make_shared<AnimatorComponent>(animRect->GetAnimClips()));
		animRect->SetAnimator(animRect->GET_COMP(Animator));
	}
}

void PlayerBullet::Update()
{
	bulletIndex += speakerSpeed * DELTA;

	if ((int)bulletIndex >= (int)totalBullet)
	{
		//	cout << bulletIndex << '\n';
		bulletIndex = 0;
	}

	// Start
	if (INPUT->Press('X'))
	{
		activation[(int)bulletIndex] = true;
		animRects[(int)bulletIndex]->SetPosition(position);
		animRects[(int)bulletIndex]->SetRotation(rotation);
	}

	SUPER::Update();

	if (activation[0] == 1 && (UINT)bulletIndex == totalBullet - 1)
		CreateBullet();

	// End
	for (int i = 0; i < (int)totalBullet; ++i)
	{
		if (animRects[i]->GetPosition().y > WIN_DEFAULT_HEIGHT + 200 || animRects[i]->GetPosition().y < -200
			|| animRects[i]->GetPosition().x > WIN_DEFAULT_WIDTH + 200 || animRects[i]->GetPosition().x < -200)
		{
			activation[i] = false;
			animRects[i]->SetPosition(Vector2(-500, -500));
		}
	}
}

void PlayerBullet::Render()
{
	SUPER::Render();
}
