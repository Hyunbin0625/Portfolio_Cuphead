#pragma once

class TutoSet
{
public:
	TutoSet();

	void SetTextID(const wstring& texturePath);
	void GUI();

	int GetSelectedIndex() { return selectedIndex; }

private:
	ScratchImage tileSprite;
	vector<ComPtr<ID3D11ShaderResourceView>> srvs;

	ImTextureID textID;

	int selectedIndex = -1;
};
