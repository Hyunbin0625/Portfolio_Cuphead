#pragma once

class Scene : public IScene
{
public:

public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	unique_ptr<Player> player;
	shared_ptr<ColorRect> ground;
};
