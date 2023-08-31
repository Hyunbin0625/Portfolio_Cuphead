#pragma once

class Tuto_Platform : public ITutoObjects
{
public:
	Tuto_Platform() : Tuto_Platform(Vector2(), 1.0f, 0.0f, 0) {}
	Tuto_Platform(const Vector2& position, const float& totalSize, float rotation, bool bCollision);

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

	shared_ptr<ColorRect> collisionRect;
	shared_ptr<ColorRect> collisionPlat;
	shared_ptr<ColorRect> collisionCircle;

	TutoState state;

	Vector2 scale = Vector2(1404, 1455);

	Vector2 colScaleR = Vector2(350, 650);
	Vector2 colScaleP = Vector2(750, 100);
	Vector2 colScaleC = Vector2(300, 830);
	
	bool bPlatform = true;
	bool bMod = false;
	bool bDelete = false;
};
