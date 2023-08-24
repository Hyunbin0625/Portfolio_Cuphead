#pragma once

class Gui
{
	DECLARE_SINGLETON(Gui);

public:
	LRESULT MsgProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	void Resize();

	void PrintFrame();

	void Update();
	void Render();

	void TextureRectGUIS(vector<shared_ptr<class TextureRect>>& trVec, const char* name);
	void TutoObjectGUIS(vector<shared_ptr<class ITutoObjects>>& trVec, const char* name);
	void ForestEnemyGUIS(vector<shared_ptr<class IForestEnemy>>& AnVec, const char* name);
	void ForestObjectGUIS(vector<shared_ptr<class IForestObjects>>& AnVec, const char* name);

private:
	void ApplyStyle();
};
