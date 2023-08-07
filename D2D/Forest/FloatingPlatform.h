#pragma once

class FloatingPlatform : public IForestObjects
{
public:
	FloatingPlatform() : FloatingPlatform(ForestObjectType::FPlatform_a, Vector2(), 1.0f, 0.0f, 0) {}
	FloatingPlatform(ForestObjectType type, const Vector2& position, const float& totalSize, float rotation, bool bCollision, bool direction = 0, float moveScale = 0.0f);

public:
	virtual bool Collision(shared_ptr<Player> player) override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void GUI(int ordinal) override;

	virtual shared_ptr<AnimationRect> GetAnimRect() override { return animRect; }
	virtual shared_ptr<TextureRect> GetTextureRect() override { return textureRect; }
	virtual bool GetDelete() override { return bDelete; }
	virtual ForestObjectState GetState() override { return state; }
	virtual bool GetCollision() override { return state.bCollision; }

	virtual void SetMod(bool mod) override { this->bMod = mod; }
	virtual void SetState(ForestObjectState state) override { this->state = state; }

public:
	void Move();

private:
	shared_ptr<TextureRect> textureRect;
	shared_ptr<ColorRect> collision;

	shared_ptr<AnimationRect> animRect;

	ForestObjectState state;

	wstring path = L"";
	
	bool bPlatform = true;
	bool bDelete = 0;
	bool bMod = false;

	bool check = false;
};
