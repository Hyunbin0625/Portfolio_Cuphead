#pragma once

class Tuto_Sphere : public ITutoObjects
{
public:
	Tuto_Sphere() : Tuto_Sphere(Vector2(), 1.0f, 0.0f, 0) {}
	Tuto_Sphere(const Vector2& position, const float& totalSize, float rotation, bool bCollision);

public:
	void Init();

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
	vector<shared_ptr<Sphere>> sphereList;

	Vector2 scale = Vector2(320, 273);
	TutoState state;

	int currentParry = 0;

	bool bMod = false;
	bool bDelete = false;
};
