#pragma once

struct D3DEnumAdapterInfo;
struct D3DEnumOutputInfo;

class Graphics
{
	DECLARE_SINGLETON(Graphics);

public:
	ComPtr<ID3D11Device> GetDevice() const { return device; }
	ComPtr<ID3D11DeviceContext> GetDC() const { return deviceContext; }
	Color GetClearColor() const { return clearColor; }

	void Begin();
	void End();

public:
	void Resize(float width, float height);	// ȭ���� ����Ǿ��� ��
	void SetViewport(float width, float height);
	void SetViewport();
	void SetBackBufferToRTV();

public:
	bool GetFullScreenState();
	void SetFullScreenState(bool bFullScreen);

private:
	void EnumerateAdapters();
	bool EnumerateAdapterOutput(const shared_ptr<D3DEnumAdapterInfo>& adapterInfo);

private:
	void CreateSwapChain();
	void CreateRenderTargetView();
	void DeleteSurface();

private:
	// COM�������̽�
//	ID3D11Device* device = nullptr;	// GPU���� ����� �ڿ��� �����ϴ� ����
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceContext;
	ComPtr<IDXGISwapChain> swapChain;
	ComPtr<ID3D11RenderTargetView> rtv;		// ��ȭ��, �˹�������
	D3D11_VIEWPORT viewport = { 0 };		// ������ ����, ��������
	Color clearColor = { 0.4f, 0.4f, 0.4f, 1.0f };// clear color, float�� 4��, ����ȭ(0~1)�� ǥ��, RGBA ���� : ����

private:
	UINT numerator = 0;
	UINT denominator = 1;

	UINT gpuMemorySize = 0;
	wstring gpuDescription = L"";

	vector<shared_ptr<D3DEnumAdapterInfo>> adapterInfos;
	int selectedAdapterIndex = 0;

	vector<Vector3> resolutionList;	// �ػ� ���

	bool bVsync = false;
	bool bFullScreen = false;
};	

struct D3DEnumAdapterInfo
{
	UINT adapterOrdinal = 0;
	ComPtr<IDXGIAdapter1> adapter;
	DXGI_ADAPTER_DESC1 adapterDesc = { 0 };

	shared_ptr<D3DEnumOutputInfo> outputInfo;
};

struct D3DEnumOutputInfo
{
	ComPtr<IDXGIOutput1> output;
	DXGI_OUTPUT_DESC outputDesc = { 0 };

	UINT numerator = 0;
	UINT denominator = 1;
};