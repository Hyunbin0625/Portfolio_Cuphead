#pragma once

class Forest_Exit : public IForestObjects
{
public:
	Forest_Exit() : Forest_Exit(Vector2(), 1.0f, 0.0f, false) {}
	Forest_Exit(const Vector2& position, const float& totalSize, float rotation, bool bCollision);

public:
	virtual bool Collision(shared_ptr<Player> player) override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void GUI(int ordinal) override;

	virtual shared_ptr<AnimationRect> GetAnimRect() override { return nullptr; }
	virtual shared_ptr<TextureRect> GetTextureRect() override { return textureRect; }
	virtual bool GetDelete() override { return bDelete; }
	virtual ForestObjectState GetState() override { return state; }
	virtual bool GetCollision() override { return state.bCollision; }

	virtual void SetMod(bool mod) override { this->bMod = mod; }
	virtual void SetState(ForestObjectState state) override { this->state = state; }

public:
	bool GetNextScene() { return nextScene; }

	void SetNextScene(bool nextScene) { this->nextScene = nextScene; }

private:
	shared_ptr<TextureRect> textureRect;

	Vector2 scale = Vector2(133, 152);
	ForestObjectState state;

	bool nextScene = false;
	bool bMod = false;
	bool bDelete = false;
};
