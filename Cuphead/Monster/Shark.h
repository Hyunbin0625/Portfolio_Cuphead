#pragma once

enum class SharkState
{
	None,
	Intro,
	Entry,
	Bite,
	Leave
};

class Shark
{
public:
	DECLARE_SINGLETON(Shark);

public:
	void Collision(shared_ptr<Player> player);
	void Init(Vector2 position, float size);

	void Update();
	void ItRender();
	void Render();

	void GUI();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	
private:
	shared_ptr<AnimationRect> animRect;
	shared_ptr<ColorRect> collisionRect;
	shared_ptr<AnimationRect> dust;
	
	SharkState state = SharkState::None;
	Vector2 position = Vector2(0, 0);
	float speed = 605.0f;
	float totalSize = 0.98f;

	float time = 0.0f;

	int animCount = 0;
};
