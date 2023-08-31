#include "stdafx.h"
#include "Tuto_Sphere.h"

Tuto_Sphere::Tuto_Sphere(const Vector2& position, const float& totalSize, float rotation, bool bCollision)
{
	state = { TutoType::Sphere, position, totalSize, rotation, bCollision };

	Init();
}

void Tuto_Sphere::Init()
{
	sphereList.resize((int)state.rotation);
	for (auto& sphere : sphereList)
		sphere = make_shared<Sphere>(state.position, 1.0f, 0.0f, true);

	for (int i = 0; i < sphereList.size(); ++i)
	{
		if (currentParry == i)
			sphereList[i]->SetISParrSlap(true);
		else
			sphereList[i]->SetISParrSlap(false);
	}
}

void Tuto_Sphere::Collision(shared_ptr<Player> player)
{
	sphereList[currentParry]->CheckCollision(player);
}

void Tuto_Sphere::Update()
{
	if (bMod && !(ImGui::IsAnyItemActive()) && sphereList.front()->GetAnimRect()->GET_COMP(Collider)->Intersect(INPUT->GetMousePosition()) && INPUT->Press(VK_LBUTTON))
		state.position = INPUT->GetMousePosition();

	for (int i = 0; i < sphereList.size(); ++i)
	{
		sphereList[i]->SetSize(state.totalSize);
		sphereList[i]->SetPosition(state.position + Vector2(200, 0) * i * state.totalSize);
	}

	if (!sphereList[currentParry]->GetISParrSlap())
	{
		++currentParry;
		if (currentParry >= sphereList.size())
			currentParry = 0;
		sphereList[currentParry]->SetISParrSlap(true);
	}

	for (auto& sphere : sphereList)
		sphere->Update();
}

void Tuto_Sphere::Render()
{
	for (auto& sphere : sphereList)
		sphere->Render();
}

void Tuto_Sphere::GUI(int ordinal)
{
	string objName = to_string(ordinal) + ". SphereList";

	if (ImGui::BeginMenu(objName.c_str()))
	{
		for (auto& sphere : sphereList)
			sphere->GetAnimRect()->SetOutline(true);

		ImGui::Text(objName.c_str());

		ImGui::SliderFloat2("Position", (float*)&state.position, CAMERA->GetPosition().x, CAMERA->GetPosition().x + WIN_DEFAULT_WIDTH);
		ImGui::SliderFloat("Size", &state.totalSize, 0.1f, 5.0f, "%.2f");
		if (ImGui::InputFloat("ListSize", &state.rotation))
			Init();

		ImGui::Checkbox("collision", &state.bCollision);

		if (ImGui::Button("Delete", ImVec2(50, 30)))
			bDelete = 1;

		ImGui::EndMenu();
	}
	else
	{
		for (auto& sphere : sphereList)
			sphere->GetAnimRect()->SetOutline(false);
	}
}
