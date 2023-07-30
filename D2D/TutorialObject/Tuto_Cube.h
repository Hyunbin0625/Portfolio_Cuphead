#pragma once

class Tuto_Cube : public ITutoObjects
{
public:
	Tuto_Cube() : Tuto_Cube(Vector2(), 1.0f, 0.0f, 0) {}
	Tuto_Cube(const Vector2& position, const float& totalSize, float rotation, bool bCollision);

public:
	virtual void Update() override;
	virtual void Render() override;
	virtual void GUI(int ordinal) override;

	virtual bool GetDelete() override { return bDelete; }
	virtual TutoState GetState() override { return state; }

	virtual void SetState(TutoState state) override { this->state = state; }

	virtual void Collision(shared_ptr<Player> player) override;

private:
	unique_ptr<TextureRect> textureRect;
	shared_ptr<ColorRect> collision;

	TutoState state;

	Vector2 scale = Vector2(224, 192);

	Vector2 colPos = Vector2(-10, -4);
	Vector2 colScale = Vector2(-33, -54);


	bool bDelete = 0;
};
