#include "stdafx.h"
#include "Input.h"

Input::Input() {}

Input::~Input() {}

void Input::Update()
{
	keyOldState = move(keyState);

	if (GetKeyboardState(keyState.data()))
	{
		/*
		�ֻ��� ��Ʈ(1byte)
		���� �����ӿ��� ���ȴ��� �ȴ��ȴ���

		unsigned char -> 0 ~ 255
		0000 0000 ~ 1111 1111

		������ ��Ʈ
		���Ű(CAPS LOCK)�� ���� �ִ���
		1 : On
		0 : Off

		128 = 1000 0000 = 0x80 = KEY_DOWN
		0000 0000(������ �ʾҴ�.)
		*/

		for (DWORD i = 0; i < MAX_INPUT_KEY; ++i)
		{
			keyState[i] = keyState[i] & 0x80 ? 1 : 0;	// 128 �Ǵ� 0���� ���׿����ڸ� ����� 1 �Ǵ� 0���� ����

			auto& oldState = keyOldState[i];
			auto& state = keyState[i];

			if (oldState == 0 && state == 1)
				keyMap[i] = KEY_INPUT_STATUS_DOWN;
			else if (oldState == 1 && state == 0)
				keyMap[i] = KEY_INPUT_STATUS_UP;
			else if (oldState == 1 && state == 1)
				keyMap[i] = KEY_INPUT_STATUS_PRESS;
			else
				keyMap[i] = KEY_INPUT_STATUS_NONE;
		}
	}
}

void Input::InputProc(UINT message, LPARAM lParam)
{
	// �޽��� �Լ����� ȣ���ؼ� ó��
	if (message >= WM_MOUSEFIRST && message <= WM_MOUSELAST)	// ���콺 ���� �޽�����
	{
		mousePosition.x = (float)GET_X_LPARAM(lParam);
		mousePosition.y = WIN_DEFAULT_HEIGHT - (float)GET_Y_LPARAM(lParam);

		// ���� Ŭ��(�ü������ �޾ƿ´�.)
		if (message == WM_LBUTTONDBLCLK)
			isDblClk = true;
		else
			isDblClk = false;

		mousePosition = CAMERA->UnProject(mousePosition);

	//	cout << mousePosition.x << ", " << mousePosition.y << '\n';
	}
}
