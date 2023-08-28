#pragma once

class PirateBeam
{
public:
	DECLARE_SINGLETON(PirateBeam);

public:
	void Init(Vector2 position, float totalSize);

public:
	void Update();
	void Render();

	shared_ptr<ColorRect> GetCollisionRect() { return collisionRect; }

	void SetIsEnd(bool bEnd) { this->bEnd = bEnd; }

private:
	shared_ptr<AnimationRect> animRect;
	shared_ptr<ColorRect> collisionRect;

	int count = 0;
	float totalSize = 0.0f;

	bool bEnd;
	bool bPirateBeam = 0;
};
