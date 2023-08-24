#pragma once

class SFX;
class SFXManager
{
public:
	DECLARE_SINGLETON(SFXManager);

public:
	void CreateBullet();
	void Init(const wstring& clipName, UINT id, Vector2 position, Vector2 scale, float rotation);

	void Update();
	void Render();

	int GetCurrentIndex() { return currentIndex; }
	shared_ptr<SFX> GetSFX(int index) { return sfxs[index]; }

	void SetCurrentIndex(int currentIndex) { this->currentIndex = currentIndex; }

private:
	vector<shared_ptr<SFX>> sfxs;

	UINT totalIndex;

	// Index
	int currentIndex = 0;
};
