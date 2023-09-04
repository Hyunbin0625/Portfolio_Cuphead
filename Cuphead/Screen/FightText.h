#pragma once

enum class FightTextType
{
	None,
	RunNGun,
	Boss_A,
	Boss_B,
};

class FightText
{
public:
	DECLARE_SINGLETON(FightText);

public:
	void Init(FightTextType type, bool bStart = false, bool bEnd = false);

public:
	void Update();
	void Render();

private:
	unique_ptr<AnimationRect> animRect;
	FightTextType type = FightTextType::None;

	int animCount = 0;
	float deltaTime = 0.0f;

	bool bStart = false;
	bool bEnd = false;
};
