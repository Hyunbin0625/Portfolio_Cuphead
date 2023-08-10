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

	// 임시 함수
	void CheckGround();

private:
	// Character
	shared_ptr<Player> player;
	shared_ptr<RibbyCroaks> ribbyCroaks;

	// BackGround
	unique_ptr<TextureRect> tempBackGround;

	vector<shared_ptr<IForestObjects>> objectList;
	unique_ptr<ForestObjectSet> forestObjectSet;

	bool mod = true;
};
