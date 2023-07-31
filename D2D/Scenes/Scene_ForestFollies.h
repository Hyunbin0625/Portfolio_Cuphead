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

	// �ӽ� �Լ�
	void CheckGround();

private:

	shared_ptr<Player> player;
	vector<shared_ptr<IForestEnemy>> enemyList;
	unique_ptr<ForestEnemySet> forestEnemySet;

	unique_ptr<TextureRect> skyLayer;

	unique_ptr<ColorRect> ground;
	unique_ptr<ColorRect> wall;
	unique_ptr<ColorRect> wall1;

	bool mod = 0;
};
