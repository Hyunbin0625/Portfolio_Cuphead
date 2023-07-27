#pragma once

class SuperBeam
{
public:
	SuperBeam();

public:
	void Init(Vector2 position, float totalSize, float deltaTime, float maxTime, bool bReverse);

public:
	void Update();
	void Render();

	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	void SetIsSuperBeam(bool bSuperBeam) { this->bSuperBeam = bSuperBeam; }

private:
	shared_ptr<AnimationRect> animRect;

	bool bSuperBeam = 0;
};
