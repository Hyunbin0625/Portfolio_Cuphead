#pragma once

class SceneRibbyCroaks: public IScene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

public:
	void SaveRibbyCroaks(const wstring& path = L"");
	void LoadRibbyCroaks(const wstring& path = L"");

private:
	// Character
	shared_ptr<Player> player;
	shared_ptr<RibbyCroaks> ribbyCroaks;

	// BackGround
	unique_ptr<TextureRect> tempBackGround;

	vector<shared_ptr<IForestObjects>> objectList;
	unique_ptr<ForestObjectSet> forestObjectSet;

	float deltaTime = 0.0f;

	bool bIntro = false;
	bool bEnd = false;
	bool mod = false;
};
