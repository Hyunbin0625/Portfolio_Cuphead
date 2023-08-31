#pragma once

class IrisA
{
public:
	DECLARE_SINGLETON(IrisA);

public:
	void Start();
	void End();

public:
	void Update();
	void Render();

public:
	bool GetIsAnimEnd() { return bAnimEnd; }

private:
	unique_ptr<AnimationRect> animRect;

	bool bAnimEnd = false;
};
