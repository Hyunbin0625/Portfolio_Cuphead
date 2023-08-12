#pragma once

class CroaksWind
{
public:	
	CroaksWind(float maxSpeed);

public:
	void Collision(shared_ptr<Player> player);
	void Init(Vector2 position, float totalSize);

	void Update() ;
	void Render() ;

	shared_ptr<AnimationRect> GetAnimRect()  { return animRect; }
	bool GetActivation() { return bActivation; }

	void SetActivation(bool bActivation) { this->bActivation = bActivation; }
	void SetSpeed(float speed) { this->speed = speed; }
	void SetTotalSize(float totalSize) { this->totalSize = totalSize; }

private:
	shared_ptr<AnimationRect> animRect;

	Vector2 position = Vector2();

	float totalSize = 1.0f;
	float maxSpeed = 0.0f;
	float speed = 0.0f;

	int count = 0;
	bool bActivation = false;
};
