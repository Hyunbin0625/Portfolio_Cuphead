#pragma once

enum class SquidState
{
	None,
	Intro,
	Loop,
	Leave
};

class Squid
{
public:
	DECLARE_SINGLETON(Squid);

public:
	void Collision(shared_ptr<Player> player);
	void Init(Vector2 position, float size);

	void Update();
	void Render();

	void GUI();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	
private:
	shared_ptr<AnimationRect> animRect;
	shared_ptr<AnimationRect> dust;
	
	SquidState state = SquidState::None;
	Vector2 position = Vector2(0, 0);
	float totalSize = 1.0f;

	float time = 0.0f;
	float attackTime = 8.0f;

	int animCount = 0;
};
