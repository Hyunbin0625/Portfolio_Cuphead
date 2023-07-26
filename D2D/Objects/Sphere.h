#pragma once

class Player;
class Sphere
{
public:
	Sphere(Vector2 position, Vector2 Scale, float rotation, bool parrySlap);

public:
	void CheckCollision(shared_ptr<Player> player);

	void Update();
	void Render();

	void GUI();

private:
	unique_ptr<AnimationRect> animRect;
	
	Vector2 position;
	float size = 1;
	float rotation;

	bool parrySlap;
};

