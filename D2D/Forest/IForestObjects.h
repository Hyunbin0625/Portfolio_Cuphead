#pragma once

enum class ForestObjectType
{
	None = -1,
	Ground,
	Wall,
};

struct ForestObjectState
{
	ForestObjectType type = ForestObjectType::None;

	Vector2 position;
	float totalSize = 1;
	float rotation;

	bool bCollision = 0;
};

class IForestObjects
{
public:
	IForestObjects() = default;
	virtual ~IForestObjects() = default;

public:
	virtual void Collision(shared_ptr<Player> player) = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void GUI(int ordinal) = 0;
	
	virtual shared_ptr<TextureRect> GetTextureRect() = 0;
	virtual bool GetDelete() = 0;
	virtual ForestObjectState GetState() = 0;
	virtual bool GetCollision() = 0;

	virtual void SetState(ForestObjectState state) = 0;
};
