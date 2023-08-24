#pragma once

class ScenePirate: public IScene
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
	shared_ptr<Pirate> pirate;

	// BackGround
	unique_ptr<TextureRect> backGround;

	vector<unique_ptr<BG_Cloud>> cloudList;
	vector<unique_ptr<BG_Water>> waterList;
	unique_ptr<BG_Ground> ground;

	vector<shared_ptr<IForestObjects>> objectList;
	unique_ptr<ForestObjectSet> forestObjectSet;

	float parryTime = 0.0f;
	bool mod = false;
};
