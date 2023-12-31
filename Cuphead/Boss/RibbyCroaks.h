#pragma once

enum class RibbyCroaksState
{
	None = 0,
	Idle,
	Attack,
	Intro,
	Init,
	Arm,
	Start2P,
	Start3P,
	Death
};

struct RibbyCroaksInfo
{
	Vector2 position = Vector2();
	float totalSize = 0.0f;

	bool bIntro = false;
	bool bAttack = false;
	bool bFrame = false;

	float time = 0.0f;
	int animCount = 0;
};

class RibbyCroaks
{
public:
	RibbyCroaks(RibbyCroaksInfo ribbyInfo, RibbyCroaksInfo croaksInfo, UINT maxHp, float delay);

public:
	void Collision(shared_ptr<Player> player);
	void Destroy();

	void Update();
	void Render();

	void GUI();

public:
	shared_ptr<AnimationRect> GetRibby() { return ribby; }
	shared_ptr<AnimationRect> GetCroaks() { return croaks; }
	

	int GetMaxHp() { return (int)maxHp; }
	float GetDelay() { return delay; }

	int GetHp() { return hp; }

	bool GetMod() { return bMod; }

	void SetHp(int hp) { this->hp = hp; }
	void SetHit(bool hit) { hp -= hit; }
	void SetCIntro(bool bIntro) { this->croaksInfo.bIntro = bIntro; }
	void SetMaxHp(int maxHp) { this->maxHp = maxHp; }
	void SetDelay(int delay) { this->delay = delay; }
	void SetMod(bool bMod) { this->bMod = bMod; }

private:
	shared_ptr<AnimationRect> ribby;
	shared_ptr<AnimationRect> croaks;
	unique_ptr<CroaksWind> croaksWind;
	unique_ptr<ColorRect> collisionRect;
	unique_ptr<ColorRect> collisionParry;

	RibbyCroaksInfo ribbyInfo;
	RibbyCroaksInfo croaksInfo;

	RibbyCroaksState rState = RibbyCroaksState::None;
	RibbyCroaksState cState = RibbyCroaksState::None;

	UINT currentPhase = 1;
	float SecPhase = 80.0f;
	float thrPhase = 50.0f;
	bool phaseIntro = false;

	UINT maxHp = 0;
	int hp = 0;

	mt19937 mt;

	bool bNone = false;
	bool bInit = false;
	int count = 0;
	float delay = 0.0f;
	float deltaTime = 0.0f;
	float parryTime = 0.0f;
	float bulletRotate = 0.0f;

	bool check = false;
	bool bArm = false;
	bool bParrySlap = false;
	bool bMod = false;

	// sounds
	bool bSIntroS = false;
	bool bTIntroS = false;
	bool bSAttack = false;
	bool bTAttack = false;

	bool bOpenS = false;
	bool bArmS = false;

	bool bDeathS = false;
};
