#pragma once

enum class SlotType
{
	None,
	Snake,
	Bison,
	tiger
};

class Slot
{
public:
	Slot();

public:
	void Init(Vector2 position, float totalSize);

public:
	void Update();
	void Render();

	bool GetStart() { return bStart; }
	int GetFlashCount() { return flashCount; }

	void SetType(SlotType type) { this->type = type; }
	void SetStart(bool bStart) { this->bStart = bStart; }
	void SetEnd(bool bEnd) { this->bEnd = bEnd; }

private:
	vector<unique_ptr<TextureRect>> slotList;

	Vector2 position;
	float totalSize = 1.0f;

	SlotType type = SlotType::None;
	float maxSpeed = 450.0f;
	float speed = 0.0f;
	float time = 0.0f;
	
	int count = 0;
	int flashCount = 0;

	bool bStart = false;
	bool bEnd = false;
};