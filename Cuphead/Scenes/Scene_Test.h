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

	// 임시 함수
	void CheckGround();

private:
	shared_ptr<Player> player;

	unique_ptr<Sphere> sphere;

	shared_ptr<ColorRect> ground;
	shared_ptr<ColorRect> ground2;
};
