#include "stdafx.h"
#include "Object.h"

void Object::AddComponent(const shared_ptr<Component>& component)
{
	if (components.count(component->GetName()))	// ���� �̸��� ���� ���
		return;

	component->SetOwner(this);	// ��ü�� ������(�ڱ��ڽ�)
	components.emplace(component->GetName(), component);
}

void Object::Update()
{
	for (const auto& comp : components)
		comp.second->Update();

	S = XMMatrixScalingFromVector(scale);
	R = XMMatrixRotationZ(-rotation);		// �ݽð���� �������� -�� �ٿ� �ð����
	T = XMMatrixTranslationFromVector(position);

	world = S * R * T;

	WB->SetWorld(world);
}

void Object::Render()
{
	for (const auto& comp : components)
		comp.second->Render();

	WB->SetVSBuffer(0);
}

void Object::GUI()
{
	ImGui::SliderFloat2("Translation", (float*)&position, 0, gWinWidth, "%.2f");
	ImGui::SliderFloat2("Scale", (float*)&scale, 1, gWinWidth, "%.2f");
	ImGui::SliderAngle("Rotation", &rotation);
}
