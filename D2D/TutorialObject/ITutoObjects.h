#pragma once

enum class TutoType
{
	None = -1,
	Cube,
};

struct TutoState
{
	TutoType type = TutoType::None;

	Vector2 position;
	float totalSize = 1;
	float rotation;

	bool bCollision = 0;
};

class ITutoObjects
{
public:
	ITutoObjects() = default;
	virtual ~ITutoObjects() = default;

public:
	virtual void Collision(shared_ptr<Player> player) = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void GUI(int ordinal) = 0;
	
	virtual bool GetDelete() = 0;
	virtual TutoState GetState() = 0;
	virtual bool GetCollision() = 0;

	virtual void SetState(TutoState state) = 0;
};
