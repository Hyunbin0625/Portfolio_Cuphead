#include "stdafx.h"
#include "SFXManager.h"

SFXManager::SFXManager()
{
	// �ʱ�ȭ
	totalIndex = 2;

//	sfxs.assign(this->totalIndex, make_shared<SFX>());
	sfxs.resize(totalIndex);

	for (auto& sfx : sfxs)
		sfx = make_shared<SFX>();
}

SFXManager::~SFXManager()
{
}

void SFXManager::CreateBullet()
{
	totalIndex *= 2;
	sfxs.resize(totalIndex, make_shared<SFX>());
}

void SFXManager::Init(const wstring& clipName,UINT id, Vector2 position, Vector2 scale, float rotation)
{
	// �̹� �ִ��� check
	for (int i = 0; i < sfxs.size(); ++i)
	{
		if (sfxs[i]->GetActivation())
		{
			if (sfxs[i]->GetClipName() == clipName && sfxs[i]->GetId() == id && sfxs[i]->GetActivation())
				return;
		}
	}

	cout << currentIndex << '\n';
	// ���ٸ�, Set
	sfxs[currentIndex++]->SetAnimClip(clipName, id, position, scale, rotation);
	
	// Index ����
	if (currentIndex > totalIndex - 1)
	{
		if (sfxs[0]->GetActivation())	// 0�� Ȱ��ȭ �Ǿ� ���� ��
			CreateBullet();
		else
			currentIndex = 0;
	}
}

void SFXManager::Update()
{
	for (int i = 0; i < sfxs.size(); ++i)
	{
		if (sfxs[i]->GetActivation())
			sfxs[i]->Update();
	}
}

void SFXManager::Render()
{
	for (int i = 0; i < sfxs.size(); ++i)
	{
		if (sfxs[i]->GetActivation())
			sfxs[i]->Render();
	}
}
