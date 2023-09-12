#pragma once

enum class ForestObjectType
{
	None = -1,
	Ground,
	Wall,
	Hole,
	FPlatform_a,
	FPlatform_b,
	FPlatform_c,
	Exit,
};

#pragma pack(push, 1)
struct ForestObjectState
{
	ForestObjectType type = ForestObjectType::None;

	Vector2 position = Vector2();
	float totalSize = 1;
	float rotation = 0.0f;

	bool bCollision = 0;

	bool direction = 0;	// 0 : »óÇÏ, 1 : ÁÂ¿ì
	float moveScale = 0.0f;
};
#pragma pack(pop)

class IForestObjects
{
public:
	IForestObjects() = default;
	virtual ~IForestObjects() = default;

public:
	virtual bool Collision(shared_ptr<Player> player) = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void GUI(int ordinal) = 0;
	
	virtual shared_ptr<AnimationRect> GetAnimRect() = 0;
	virtual shared_ptr<TextureRect> GetTextureRect() = 0;
	virtual bool GetDelete() = 0;
	virtual ForestObjectState GetState() = 0;
	virtual bool GetCollision() = 0;

	virtual void SetState(ForestObjectState state) = 0;
	virtual void SetMod(bool mod) = 0;
};
