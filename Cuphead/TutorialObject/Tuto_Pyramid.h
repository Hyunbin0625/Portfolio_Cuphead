#pragma once

class Tuto_Pyramid : public ITutoObjects
{
public:
	Tuto_Pyramid() : Tuto_Pyramid(Vector2(), 1.0f, 0.0f, 0) {}
	Tuto_Pyramid(const Vector2& position, const float& totalSize, float rotation, bool bCollision);

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
	unique_ptr<TextureRect> texturePrmid;
	unique_ptr<AnimationRect> animTarget;

	shared_ptr<ColorRect> collisionRect;

	TutoState state;

	Vector2 scaleR = Vector2(288, 321);
	Vector2 scaleP = Vector2(226, 190);
	Vector2 scaleT = Vector2(77, 91);

	Vector2 colScaleR = Vector2(215, 250);

	int hp = 3;
	
	bool bActivation = true;
	bool bPlatform = false;
	bool bMod = false;
	bool bDelete = false;
};
