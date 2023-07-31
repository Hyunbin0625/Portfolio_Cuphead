﻿#include "stdafx.h"
#include "ForestEnemySet.h"

ForestEnemySet::ForestEnemySet()
{
	SetTextID(L"_Textures/Enemy/flowergrunt_Icon.png");
}

void ForestEnemySet::SetTextID(const wstring& texturePath)
{
	HRESULT hr = LoadFromWICFile(texturePath.c_str(), WIC_FLAGS_NONE, nullptr, tileSprite);
	CHECK(hr);

	hr = CreateShaderResourceView(DEVICE.Get(), tileSprite.GetImages(), tileSprite.GetImageCount(), tileSprite.GetMetadata(), &srv);
	CHECK(hr);

	textID.push_back(srv.Get());
}

void ForestEnemySet::GUI()
{
	static bool bOpen = true;
	if (ImGui::Begin("ForestEnemies", &bOpen))
	{
		int index = 0;
		selectedIndex = -1;

		for (UINT i = 0; i < textID.size(); ++i)
		{
			ImGui::PushID(index++);	// ﻿ImGui가 버튼들에 대해서 자체적으로 구별하기 위한 ID 생성

			if (ImGui::ImageButton(textID[i], ImVec2(40, 40)))
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