#pragma once

class Tuto_Cylinder : public ITutoObjects
{
public:
	Tuto_Cylinder() : Tuto_Cylinder(Vector2(), 1.0f, 0.0f, 0) {}
	Tuto_Cylinder(const Vector2& position, const float& totalSize, float rotation, bool bCollision);

public:
	virtual void Collision(shared_ptr<Player> player) override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void GUI(int ordinal) override;

	virtual bool GetDelete() override { return bDelete; }
	virtual TutoState GetState() override { return state; }
	virtual bool GetCollision() override { return state.bCollision; }

	virtual void SetState(TutoState state) override { this->state = state; }
	virtual void SetIsMod(bool bMod) override { this->bMod = bMod; }

private:
	unique_ptr<TextureRect> textureRect;
	shared_ptr<ColorRect> collision;

	TutoState state;

	Vector2 scale = Vector2(224, 393);

	Vector2 colScale= Vector2(170, 330);
	
	bool bPlatform = false;
	bool bMod = false;
	bool bDelete = false;
};
