#pragma once

class ForestObjectSet
{
public:
	ForestObjectSet();

	void SetTextID(const wstring& texturePath);
	void GUI();

	int GetSelectedIndex() { return selectedIndex; }

private:
	ScratchImage tileSprite;
	ComPtr<ID3D11ShaderResourceView> srv;

	vector<ImTextureID> textID;

	int selectedIndex = -1;
};
