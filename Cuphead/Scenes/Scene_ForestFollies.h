#pragma once

class SceneForestFollies: public IScene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

public:
	void SaveForestFolliesMap(const wstring& path = L"");
	void LoadForestFolliesMap(const wstring& path = L"");

	void Collision();

private:
	shared_ptr<Player> player;

	vector<shared_ptr<IForestEnemy>> enemyList;
	unique_ptr<ForestEnemySet> forestEnemySet;

	vector<shared_ptr<IForestObjects>> objectList;
	unique_ptr<ForestObjectSet> forestObjectSet;

	vector<shared_ptr<TextureRect>> trRectList;

	unique_ptr<TextureRect> skyLayer;

	float deltaTime = 0.0f;

	bool nextScene = false;
	bool bIntro = false;
	bool mod = false;
};
