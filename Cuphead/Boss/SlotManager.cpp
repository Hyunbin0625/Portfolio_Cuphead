#include "stdafx.h"
#include "SlotManager.h"

SlotManager::SlotManager()
{
	slotList.resize(3);

	for (auto& slot : slotList)
		slot = make_unique<Slot>();

	random_device random;
	mt = mt19937(random());

	SOUND->AddSound("MspinLP3", L"_Sounds/sfx_level_frogs_morphed_dial_spin_loop_01.wav", true);
}

SlotManager::~SlotManager() {}

void SlotManager::Init(Vector2 position, float totalSize)
{
	bStart = false;
	bResult = false;
	bEnd = false;
	bActivation = true;
	time = 0.0f;
	this->position = position;
	this->totalSize = totalSize;

	slotList[0]->Init(Vector2(position.x - 140 * totalSize, position.y - 27 * totalSize), totalSize);
	slotList[1]->Init(Vector2(position.x - 81 * totalSize, position.y - 29 * totalSize), totalSize);
	slotList[2]->Init(Vector2(position.x - 18 * totalSize, position.y - 32 * totalSize), totalSize);
}

void SlotManager::Start()
{
	bStart = true;
	bSpinS = false;
//	uniform_int_distribution<int> randomSlotType(1, 3);
	type = (SlotType)count;
	for (auto& slot : slotList)
		slot->SetType(type);

	++count;
	if (count > 3)
		count = 1;
}

void SlotManager::Update()
{
	if (bStart)
	{
		if (!bSpinS)
		{
			bSpinS = true;
			SOUND->Play("MspinLP3");
		}
		time += DELTA;

		// animation
		for (int i = 0; i < 3; ++i)
		{
			if (!bResult && ((i < 1) || (i < 2 && time >= 0.1f) || (i < 3 && time >= 0.2f)))
				slotList[i]->SetStart(true);
			if ((i < 1 && time >= 2.5f) || (i < 2 && time >= 2.8f) || (i < 3 && time >= 3.1f))
			{
				bResult = true;
				slotList[i]->SetStart(false);
				slotList[i]->SetEnd(true);
				SOUND->Stop("MspinLP3");
			}
		}
		if (slotList.back()->GetFlashCount() >= 3)
		{
			bEnd = true;
			bStart = false;
			time = 0.0f;
		}
	}

	for (auto& slot : slotList)
		slot->Update();
}

void SlotManager::Render()
{
	if (bActivation)
	{
		for (auto& slot : slotList)
			slot->Render();
	}
}
