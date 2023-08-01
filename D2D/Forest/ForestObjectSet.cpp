#include "stdafx.h"
#include "ForestObjectSet.h"


ForestObjectSet::ForestObjectSet()
{
	SetTextID(L"_Textures/ground.png");
	SetTextID(L"_Textures/wall.png");
}

void ForestObjectSet::SetTextID(const wstring& texturePath)
{
	HRESULT hr = LoadFromWICFile(texturePath.c_str(), WIC_FLAGS_NONE, nullptr, tileSprite);
	CHECK(hr);

	hr = CreateShaderResourceView(DEVICE.Get(), tileSprite.GetImages(), tileSprite.GetImageCount(), tileSprite.GetMetadata(), &srv);
	CHECK(hr);

	textID.push_back(srv.Get());
}

void ForestObjectSet::GUI()
{
	static bool bOpen = true;
	if (ImGui::Begin("ForestObjects", &bOpen))
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
