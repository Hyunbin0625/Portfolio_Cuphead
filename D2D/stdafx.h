#pragma once

#define NOMINMAX

// �ܼ�â ���
#ifdef _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif 

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include <windows.h>
#include <windowsx.h>
#include <commdlg.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <cassert>

// C++ ��Ÿ�� ��� �����Դϴ�.
#include <string>
#include <memory>
#include <iostream>
#include <array>
#include <chrono>
#include <vector>
#include <map>
#include <fstream>
#include <unordered_map>
#include <random>

using namespace std;

//DirectX D3D11
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//WRL
#include <wrl.h>
using namespace Microsoft;
using namespace WRL;

//DirectXKT
#include "_Libraries/DirectXTK/SimpleMath.h"
using namespace DirectX;
using namespace SimpleMath;

//DirectXTex
#include <DirectXTex.h>

// ImGui
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

// FMOD
#include "_Libraries/FMOD/fmod.hpp"
#ifdef _M_X64
	#pragma comment(lib, "_Libraries/FMOD/x64/fmodL_vc.lib")
#elif _M_IX86
	#pragma comment(lib, "_Libraries/FMOD/x86/fmodL_vc.lib")
#endif

// Macros
#define WIN_DEFAULT_WIDTH 1280.0f
#define WIN_DEFAULT_HEIGHT 720.0f

#define CHECK(hr) assert(SUCCEEDED(hr))

#define CENTER (Vector2(WIN_DEFAULT_WIDTH, WIN_DEFAULT_HEIGHT) / 2.0f)
#define CENTER_X (WIN_DEFAULT_WIDTH / 2)
#define CENTER_Y (WIN_DEFAULT_HEIGHT / 2)

#define RIGHT Vector2(1.0f, 0.0f)
#define UP Vector2(0.0f, 1.0f)

#define RED Color(1, 0, 0, 1)
#define GREEN Color(0, 1, 0, 1)
#define BLUE Color(0, 0, 1, 1)
#define YELLOW Color(1, 1, 0, 1)
#define MAGENTA Color(1, 0, 1, 1)
#define CYAN Color(0, 1, 1, 1)
#define WHITE Color(1, 1, 1, 1)
#define BLACK Color(0, 0, 0, 1)

#define SUPER __super

//Singleton
#define DECLARE_SINGLETON(CLASS_NAME)							\
private:														\
	CLASS_NAME();												\
	~CLASS_NAME();												\
	CLASS_NAME(const CLASS_NAME& other) = delete;				\
	CLASS_NAME& operator=(const CLASS_NAME& other) = delete;	\
public:															\
	static CLASS_NAME* Get()									\
	{															\
		static CLASS_NAME instance;								\
		return &instance;										\
	}

//ExternGlobals
extern HWND gHandle;
extern float gWinWidth;
extern float gWinHeight;

//Systems
#include "Systems/Input.h"
#include "Systems/Time.h"
#include "Systems/Graphics.h"
#include "Systems/Gui.h"
#include "Systems/Sound.h"
#include "Systems/Camera.h"
#include "Systems/SFXManager.h"
#include "Systems/UI.h"

#define INPUT Input::Get()
#define TIME Time::Get()
#define DELTA Time::Get()->GetDeltaTime()
#define GRAPHICS Graphics::Get()
#define DEVICE Graphics::Get()->GetDevice()
#define DC Graphics::Get()->GetDC()
#define IMGUI Gui::Get()
#define SOUND Sound::Get()
#define CAMERA Camera::Get()
#define SFXMANAGER SFXManager::Get()
#define UI Ui::Get()

// Renders
#include "Renders/Resources/VertexType.h"
#include "Renders/IA/VertexBuffer.h"
#include "Renders/IA/IndexBuffer.h"
#include "Renders/Shaders/IShader.h"
#include "Renders/Shaders/VertexShader.h"
#include "Renders/IA/InputLayout.h"
#include "Renders/Shaders/PixelShader.h"
#include "Renders/Resources/ConstantBuffer.h"
#include "Renders/Resources/GlobalBuffers.h"

// Utilities
#include "Utilities/Collision.h"
#include "Utilities/RenderTexture.h"
#include "Utilities/String.h"
#include "Utilities/Path.h"
#include "Utilities/Animator.h"

// Components
#include "Components/Component.h"
#include "Components/ColorComponent.h"
#include "Components/MoveComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/SelectionComponent.h"
#include "Components/AnimatorComponent.h"

// Objects
#include "Objects/Object.h"
#include "Objects/Drawable.h"
#include "Objects/ColorRect.h"
#include "Objects/TextureRect.h"
#include "Objects/AnimationRect.h"
#include "Objects/Sphere.h"
#include "Objects/SFX.h"
#include "Objects/SuperMeterCard.h"

// Bullet
#include "Bullet/PlayerBullet.h"
#include "Bullet/PlayerBulletManager.h"
#include "Bullet/PlayerSpecialAttack.h"
#include "Bullet/PlayerSpecialAttackManager.h"
#include "Bullet/SuperBeam.h"

// Character
#include "Character/Player.h"

// GetComponentMacro
#define GET_COMP(COMPONENT_NAME) GetComponent<COMPONENT_NAME##Component>(#COMPONENT_NAME)	// ## : �̾� ���δ�. ��ũ�� ġȯ, # : ���ڿ��� ġȯ�� �ȴ�.

// Scenes
#include "Scenes/IScene.h"

// Tuto
#include "TutorialObject/ITutoObjects.h"
#include "Forest/IForestEnemy.h"
#include "Forest/IForestObjects.h"

// Tuto
#include "TutorialObject/TutoSet.h"
#include "TutorialObject/Tuto_Cube.h"

// Forest
#include "Forest/ForestEnemySet.h"
#include "Forest/FlowerGrunt.h"
#include "Forest/Blob.h"
#include "Forest/Mushroom.h"
#include "Forest/MRPoisonManager.h"
#include "Forest/Lobber.h"
#include "Forest/LSeedManager.h"
#include "Forest/Chomper.h"
#include "Forest/Spiker.h"
#include "Forest/Acorn.h"
#include "Forest/AcornMachine.h"

#include "Forest/ForestObjectSet.h"
#include "Forest/Forest_Ground.h"
#include "Forest/Forest_Wall.h"