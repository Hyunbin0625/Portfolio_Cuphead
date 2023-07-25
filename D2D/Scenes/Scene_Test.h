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

	// �ӽ� �Լ�
	void CheckGround();

private:
	unique_ptr<Player> player;
	shared_ptr<ColorRect> ground;

	shared_ptr<ColorRect> ground2;
};
