#pragma once

class SFX
{
public:
	SFX();

public:
	void SetAnimClip(const wstring& clipName, UINT id, Vector2 position, Vector2 scale, float rotation);

public:
	void Update();
	void Render();

	shared_ptr<AnimationRect> GetAnimRect() { return animRect; }
	wstring GetClipName() { return clipName; }
	UINT GetId() { return id; }
	bool GetActivation() { return activation; }

private:
	shared_ptr<AnimationRect> animRect;

	wstring clipName;
	UINT id = 0;

	bool activation = 0;
};
