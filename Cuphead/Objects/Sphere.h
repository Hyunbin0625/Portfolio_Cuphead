#pragma once

class Player;
class Sphere
{
public:
	Sphere(Vector2 position, float size, float rotation, bool parrySlap);

public:
	void CheckCollision(shared_ptr<Player> player);

	void Update();
	void Render();

	void GUI();

public:
	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	bool GetISParrSlap() { return bParrySlap; }

	void SetPosition(Vector2 position) { this->position = position; }
	void SetSize(float size) { this->size = size; }
	void SetISParrSlap(bool bParrySlap) { this->bParrySlap = bParrySlap; }

private:
	shared_ptr<AnimationRect> animRect;
	
	Vector2 position = Vector2();
	float size = 1.0f;
	float rotation = 0.0f;

	bool bParrySlap = false;
};

