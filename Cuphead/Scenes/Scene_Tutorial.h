#pragma once

class SceneTutorial : public IScene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

public:
	void SaveTutorialMap(const wstring& path = L"");
	void LoadTutorialMap(const wstring& path = L"");

	// 임시 함수
	void CheckGround();

private:
	shared_ptr<Player> player;

	unique_ptr<TextureRect> backLayer;
	unique_ptr<TextureRect> frontLayer;

	unique_ptr<ColorRect> ground;

	vector<shared_ptr<ITutoObjects>> objectList;

	unique_ptr<class TutoSet> tutoSet;
};
