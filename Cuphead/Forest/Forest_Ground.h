#pragma once

class Forest_Ground : public IForestObjects
{
public:
	Forest_Ground() : Forest_Ground(Vector2(), 1.0f, 0.0f, false, false) {}
	Forest_Ground(const Vector2& position, const float& totalSize, float rotation, bool bCollision, bool platform);

public:
	virtual void Update() override;
	virtual void Render() override;
	virtual void GUI(int ordinal) override;

	virtual bool Collision(shared_ptr<Player> player) override;
	
	virtual shared_ptr<AnimationRect> GetAnimRect() override { return nullptr; }
	virtual shared_ptr<TextureRect> GetTextureRect() override { return textureRect; }
	virtual bool GetDelete() override { return bDelete; }
	virtual ForestObjectState GetState() override { return state; }
	virtual bool GetCollision() override { return state.bCollision; }

	virtual void SetState(ForestObjectState state) override { this->state = state; }
	virtual void SetMod(bool mod) override { this->bMod = mod; }

	Vector2 RotateCoordinate(Vector2 p, float theta, Vector2 base);

private:
	shared_ptr<TextureRect> textureRect;

	ForestObjectState state;
	Vector2 scale = Vector2(240, 61);

	bool bDelete = 0;
	bool bMod = false;
};
