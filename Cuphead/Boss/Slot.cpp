#include "stdafx.h"
#include "Slot.h"

Slot::Slot()
{
	slotList.resize(2);

	for (auto& slot : slotList)
		slot = make_unique<TextureRect>(Vector2(1000, -1000), Vector2(66, 130), 0.0f, L"_Textures/RibbyCroaks/tallfrog_slotman_slot_TEMP.png");

	SOUND->AddSound("MspinEP3", L"_Sounds/sfx_frogs_morphed_spin_01.wav", false, true);
}

void Slot::Init(Vector2 position, float totalSize)
{
	bStart = false;
	bEnd = false;
	bSpinES = false;
	count = 0;
	time = 0.0f;
	flashCount = 0;
	speed = maxSpeed;
	this->position = position;
	this->totalSize = totalSize;

	for (auto& slot : slotList)
	{
		wstring path = L"_Textures/RibbyCroaks/tallfrog_slotman_slot_TEMP.png";
		slot->SetSRV(path);
	}

	slotList[0]->SetPosition(Vector2(position.x, position.y));
	slotList[1]->SetPosition(Vector2(slotList[0]->GetPosition().x, slotList[0]->GetPosition().y + slotList[0]->GetScale().y - 14));
	// 나중에 각 slot들 위치, scale set
}

void Slot::Update()
{
	if (bStart)
	{
		// animation
		for (auto& slot : slotList)
		{
			slot->Move(Vector2(0, 1) * -speed);
			if (slot->GetPosition().y <= position.y - 104.0f)
				slot->SetPosition(Vector2(slot->GetPosition().x, slot->GetPosition().y + slot->GetScale().y * 2 - 14));
		}
	}
	else if (bEnd)
	{
		if (slotList[1]->GetPosition().y <= position.y - 104.0f)
			slotList[1]->SetPosition(Vector2(slotList[1]->GetPosition().x, slotList[1]->GetPosition().y + slotList[1]->GetScale().y * 2 - 14));
		if (slotList[0]->GetPosition().y <= position.y - 104.0f && count == 0)
		{
			slotList[0]->SetPosition(Vector2(slotList[0]->GetPosition().x, slotList[0]->GetPosition().y + slotList[0]->GetScale().y * 2 - 14));
			++count;
		}
		else if (count == 0)
		{
			for (auto& slot : slotList)
				slot->Move(Vector2(0, 1) * -speed);
		}
		else if (count <= 2)
		{
			if (!bSpinES)
			{
				bSpinES = true;
				SOUND->Play("MspinEP3");
			}

			switch (type)
			{
			case SlotType::Snake:
				if (count == 1 && slotList[0]->GetPosition().y <= position.y - 44.0f)
					++count;
				else if (count == 1)
				{
					for (auto& slot : slotList)
						slot->Move(Vector2(0, 1) * -speed);
				}
				else if (count == 2)
				{
					float distance = position.y - slotList[0]->GetPosition().y;
					for (auto& slot : slotList)
					{
						slot->Move(Vector2(0, distance) * 4);
					}
					if (distance < 0.1)
						++count;
				}
				break;
			case SlotType::Bison:
				if (count == 1 && slotList[0]->GetPosition().y <= position.y)
					++count;
				else if (count == 1)
				{
					for (auto& slot : slotList)
						slot->Move(Vector2(0, 1) * -speed);
				}
				else if (count == 2)
				{
					float distance = (position.y + 44.0f) - slotList[0]->GetPosition().y;
					for (auto& slot : slotList)
					{
						slot->Move(Vector2(0, distance) * 4);
					}
					if (distance < 0.1)
						++count;
				}
				break;
			case SlotType::tiger:
				if (count == 1 && slotList[0]->GetPosition().y <= position.y + 43.0f)
					++count;
				else if (count == 1)
				{
					for (auto& slot : slotList)
						slot->Move(Vector2(0, 1) * -speed);
				}
				else if (count == 2)
				{
					float distance = (position.y + 87.0f) - slotList[0]->GetPosition().y;
					for (auto& slot : slotList)
					{
						slot->Move(Vector2(0, distance) * 4);
					}
					if (distance < 0.1)
						++count;
				}
				break;
			}
		}
		else
		{
			if (time == 0.0f)
			{
				++flashCount;
				for (auto& slot : slotList)
				{
					wstring path = L"_Textures/RibbyCroaks/tallfrog_slotman_slot_flash_TEMP.png";
					slot->SetSRV(path);
				}
			}
			else if (time >= 0.1f)
			{
				for (auto& slot : slotList)
				{
					wstring path = L"_Textures/RibbyCroaks/tallfrog_slotman_slot_TEMP.png";
					slot->SetSRV(path);
				}
			}
			
			if (time >= 0.6f)
				time = 0.0f;
			else
				time += DELTA;
		}
	}

	slotList[0]->SetScale(Vector2(66, 130) * totalSize);

	for (auto& slot : slotList)
		slot->Update();
}

void Slot::Render()
{
	for (auto& slot : slotList)
		slot->Render();
}
