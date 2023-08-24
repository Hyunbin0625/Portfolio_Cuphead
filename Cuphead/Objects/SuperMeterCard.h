#pragma once

class SuperMeterCard
{
public:
	SuperMeterCard();

public:
	void Update();
	void Render();

	bool GetActivation() { return activation; }
	Vector2 GetPosition() { return position; }

	void SetActivation(bool activation) { this->activation = activation; }
	void SetPosition(Vector2 position) { this->position = position; }

private:
	shared_ptr<AnimationRect> animRect;
	bool activation = 0;

	Vector2 position;
};
