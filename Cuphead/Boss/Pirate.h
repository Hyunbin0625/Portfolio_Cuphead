#pragma once

enum class PirateState
{
	None = 0,
	Idle,
	Attack,
	Whistle,
	Intro,
	Start2P,
	Death
};

struct PirateInfo
{
	Vector2 position = Vector2();
	float totalSize = 0.0f;
	float delayTime = 0.0f;

	bool bAttack = false;
	bool bFrame = false;

	float time = 0.0f;
	int animClipCount = 0;
	bool subAnimRect = false;
	bool bDeath = false;
};

class Pirate
{
public:
	Pirate(PirateInfo captainInfo, PirateInfo boatInfo, UINT maxHp, float waveValue);

public:
	void Collision(shared_ptr<Player> player);

	void Update();
	void Render();

	void BRender();

	void GUI();

public:
	shared_ptr<AnimationRect> GetCaptain() { return captain; }
	shared_ptr<AnimationRect> GetBoat() { return fBoat; }

	int GetMaxHp() { return (int)maxHp; }

	int GetHp() { return hp; }

	bool GetMod() { return bMod; }

	void SetHp(int hp) { this->hp = hp; }
	void SetHit(bool hit) { hp -= hit; }
	void SetCIntro(bool bIntro) { this->bIntro = bIntro; }
	void SetMaxHp(int maxHp) { this->maxHp = maxHp; }
	void SetMod(bool bMod) { this->bMod = bMod; }

private:
	shared_ptr<AnimationRect> captain;
	shared_ptr<AnimationRect> tCaptain;
	shared_ptr<AnimationRect> fBoat;
	shared_ptr<AnimationRect> mBoat;
	shared_ptr<AnimationRect> bBoat;

	int tempva = 0;

	PirateInfo captainInfo;
	PirateInfo boatInfo;

	PirateState cState = PirateState::Idle;
	PirateState bState = PirateState::Idle;

	UINT maxHp = 0;
	int hp = 0;

	mt19937 mt;

	UINT currentPhase = 1;
	float SecPhase = 40.0f;
	float bAttackPer = 30.0f;
	bool phaseIntro = false;

	bool bNone = false;
	bool bInit = false;
	int count = 0;
	float deltaTime = 0.0f;
	float bulletRotate = 0.0f;

	bool direction = true;
	float waveValue = 0.0f;
	float speed = 0.0f;
	Vector2 defPos = Vector2();

	bool check = false;
	bool bWhistle = false;
	bool bIntro = false;
	bool bMod = false;
};
