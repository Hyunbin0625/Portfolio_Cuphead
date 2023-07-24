#pragma once

class Bullet
{
public:
	Bullet(UINT totalBullet, float bulletSpeed, float speakerSpeed);
	virtual ~Bullet() = default;

public:
	virtual void Update();
	virtual void Render();

public:
	UINT GetTotalBullet() { return totalBullet; }
	shared_ptr<AnimationRect> GetTextureRect(int index) { return animRects[index]; }
	vector<shared_ptr<AnimationRect>> GetTextureRects() { return animRects; }

	void SetActivation(int index, bool activation) { this->activation[index] = activation; }

protected:
	float bulletIndex = 0;
	UINT totalBullet = 0;

	float maxSpeed = 0;
	float speed = 0;
	float speakerSpeed = 0;

	vector<shared_ptr<AnimationRect>> animRects;
	vector<bool> activation;
};
