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

	// 임시 함수
	void CheckGround();

private:
	shared_ptr<Player> player;

	unique_ptr<TextureRect> backLayer;
	unique_ptr<TextureRect> frontLayer;

	unique_ptr<ColorRect> ground;
};
