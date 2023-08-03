#pragma once

class ForestEnemySet
{
public:
	ForestEnemySet();

	void SetTextID(const wstring& texturePath);
	void GUI();

	int GetSelectedIndex() { return selectedIndex; }

private:
	ScratchImage tileSprite;
	vector<ComPtr<ID3D11ShaderResourceView>> srvs;
	
	ImTextureID textID;

	int selectedIndex = -1;
};

