#pragma once

enum Button
{
	Start = 0,
	Mod,
	Option,
	End
};

class SceneMain : public IScene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

public:
	void Reset();

	bool GetStart() { return bStart; }
	bool GetMod() { return bMod; }
	bool GetOption() { return bOption; }
	bool GetEnd() { return bEnd; }

private:
	unique_ptr<TextureRect> startButton;
	unique_ptr<TextureRect> modButton;
	unique_ptr<TextureRect> optionButton;
	unique_ptr<TextureRect> endButton;

	unique_ptr<TextureRect> background;

	int CurrentButton = 0;

	bool bStart = false;
	bool bMod = false;
	bool bOption = false;
	bool bEnd = false;
};
