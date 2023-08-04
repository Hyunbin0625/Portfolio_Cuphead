#include "stdafx.h"
#include "ForestEnemySet.h"

ForestEnemySet::ForestEnemySet()
{
	SetTextID(L"_Textures/Enemy/flowergrunt_Icon.png");
	SetTextID(L"_Textures/Enemy/blob_Icon.png");
	SetTextID(L"_Textures/Enemy/mushroom_Icon.png");
	SetTextID(L"_Textures/Enemy/lobber_Icon.png");
}

void ForestEnemySet::SetTextID(const wstring& texturePath)
{
	HRESULT hr = LoadFromWICFile(texturePath.c_str(), WIC_FLAGS_NONE, nullptr, tileSprite);
	CHECK(hr);

	srvs.push_back(nullptr);
	hr = CreateShaderResourceView(DEVICE.Get(), tileSprite.GetImages(), tileSprite.GetImageCount(), tileSprite.GetMetadata(), &srvs[srvs.size() - 1]);
	CHECK(hr);
}

void ForestEnemySet::GUI()
{
	static bool bOpen = true;
	if (ImGui::Begin("ForestEnemies", &bOpen))
	{
		int index = 0;
		selectedIndex = -1;

		for (UINT i = 0; i < srvs.size(); ++i)
		{
			ImGui::PushID(index++);	// ﻿ImGui가 버튼들에 대해서 자체적으로 구별하기 위한 ID 생성

			textID = srvs[i].Get();
			if (ImGui::ImageButton(textID, ImVec2(40, 40)))
			{
				selectedIndex = i;
			}

			ImGui::PopID();

			if (index % 4 != 0)
				ImGui::SameLine();
		}
	}
	ImGui::End();
}