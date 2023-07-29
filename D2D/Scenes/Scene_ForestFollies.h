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

	// �ӽ� �Լ�
	void CheckGround();

private:

	shared_ptr<Player> player;

	unique_ptr<TextureRect> skyLayer;

	unique_ptr<ColorRect> ground;
};
