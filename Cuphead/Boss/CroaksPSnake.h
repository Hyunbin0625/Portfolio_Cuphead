#pragma once

class CroaksPSnake
{
public:	
	CroaksPSnake();

public:
	void Collision(shared_ptr<Player> player);
	void GroundCollision();
	void Init(Vector2 position, float groundY);

	void Update();
	void Render();

	shared_ptr<AnimationRect> GetAnimRect()  { return animRect; }
	bool GetActivation() { return bActivation; }
	float GetSpeed() { return speed; }

	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }
	void SetSpeed(float speed) { this->speed = speed; }
	void SetGround(bool bGround) { this->bGround = bGround; }
	void SetActivation(bool bActivation) { this->bActivation = bActivation; }

private:
	shared_ptr<AnimationRect> animRect;
	shared_ptr<ColorRect> collisionRect;

	float totalSize = 1.0f;
	float speed = 0.0f;
	float vel = 0.0f;
	float coef_res = 0.0f;

	float groundY = 0.0f;
	bool bGround = false;
	bool bActivation = false;
};
