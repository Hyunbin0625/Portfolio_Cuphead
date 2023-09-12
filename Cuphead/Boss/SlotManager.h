#pragma once

class SlotManager
{
public:
	DECLARE_SINGLETON(SlotManager);

public:
	void Init(Vector2 position, float totalSize);
	void Start();

public:
	void Update();
	void Render();

	SlotType GetType() { return type; }
	bool GetEnd() { return bEnd; }

	void SetActivation(bool bActivation) { this->bActivation = bActivation; }

private:
	vector<unique_ptr<Slot>> slotList;
	SlotType type = SlotType::None;
	int count = 2;
	mt19937 mt;

	Vector2 position;
	float totalSize = 1.0f;

	float time = 0.0f;

	bool bStart = false;
	bool bResult = false;
	bool bEnd = false;

	bool bActivation = false;

	// Sounds
	bool bSpinS = false;
};