#pragma once

class AnimationRect;
class SuperMeterCard;
class Ui
{
public:
	DECLARE_SINGLETON(Ui);

public:
	void Init(Vector2 position, UINT currentHp, int cardPoint);

public:
	void Update();
	void Render();

private:
	unique_ptr<AnimationRect> hp;
	vector<shared_ptr<SuperMeterCard>> superMeterCards;

};
