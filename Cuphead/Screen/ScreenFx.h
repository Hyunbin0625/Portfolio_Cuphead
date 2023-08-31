#pragma once

class ScreenFx
{
public:
	DECLARE_SINGLETON(ScreenFx);

public:
	void Start();

public:
	void Update();
	void Render();

private:
	unique_ptr<AnimationRect> animRect;

	int clipCount = 0;

	bool bActivation = false;
};
