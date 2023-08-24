#include "stdafx.h"
#include "Time.h"

Time::Time()
{
	// �ʱ�ȭ
	lastTime = chrono::steady_clock::now();
}

Time::~Time() {}

void Time::Update()
{
	currentTime = chrono::steady_clock::now();	// ���� �ð��� ������ ������ ��ȯ�ϴ� �Լ�
	chrono::duration<double> delta = currentTime - lastTime;
	deltaTime = delta.count();

	lastTime = currentTime;
	worldTime += deltaTime;	// �帥�ð� ����

	fpsTimeElpased += deltaTime;	// deltaTime ����
	++frameCount;

	if (fpsTimeElpased >= 1.0)
	{
		fps = frameCount;
		frameCount = 0;
		fpsTimeElpased = 0.0;

//		CheckTime();
	}
}