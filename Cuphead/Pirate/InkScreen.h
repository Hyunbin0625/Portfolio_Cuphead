#pragma once

class InkScreen
{
public:
	DECLARE_SINGLETON(InkScreen);

public:
	void Init(float duration);

public:
	void Update();
	void Render();

private:
	vector<shared_ptr<AnimationRect>> animRectList;
	mt19937 mt;

	Vector2 MScale = Vector2(0.2f, 2.0f);

	float time = 0.0f;
	float duration = 0.0f;

	bool bActivation = false;
};
