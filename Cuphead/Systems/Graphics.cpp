#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics()
{
    EnumerateAdapters();
    CreateSwapChain();
}

Graphics::~Graphics() {}

/*
    GPU���� ����� �ڿ�(�ٽ�)
    ũ�� ������
    Buffer : CPU���� GPU�� ������ �����ϰ� ���� �� �ӽ÷� ��� ����
    Texture : ���� � �׸� ���� �� �����ϰ� ������, ������ �ݵ�� �׸��� ������ �ʴ´�.

    Buffer �ε���, ����, ���
    texture 1d, 2d, 3d

    GPU���� ����� ������ ����
    shader HLSL(High Level Shader Language)
    �ΰ��� Ȱ���ϱ� ���� ���·� shader�� �ۼ��� �� �ִ�.
    ������(Compile) �ϴ� ������ �ʿ��ϴ�.

    �ڿ���
    ���� ����, �ε��� ����, ��� ����
    �ڿ��� ���� ���������ο� �Ⱦ� �� �� �ִ�.(�и��� �������� �����ϱ� ������)

    Texture : �׸�, �ִϸ��̼� �� ���������� ������ ���� �� �ֱ� ������ �뵵�� ��Ȯ���� �ʱ� ������
    �ڿ��並 ���� ������ ��, �ڿ��並 ������ ���������ο� �Ⱦ��ش�. ���� ����� �ڿ��� �Ѿ�� � �뵵���� ��Ȯ�ϰ� �� �� �ִ�.

    ���ҽ� ��
    ���ε����� ���ҽ��� ��� ������� �����ϴ� ��

    RTV(RenderTargetView)
    ����۸� ���� �� ���
    ��ȭ���� ����
    ShaderResourceView
    �ڿ��� shader���� ���� �� ���
    �ڿ��� ShaderResourceView ���·� ���� shader�� �Ѱ� �� �� �ִ�.
    DepthStencilView
    ���� ǥ���� �ϴ� ��
    UnorderedAccessView
    */

void Graphics::Begin()
{
    SetViewport();
    SetBackBufferToRTV();
}

void Graphics::End()
{
    // �� �׸��� swapchiain�� ���� frontBuffer�� swap
    HRESULT hr = swapChain->Present(1, 0);   // ���� ����ȭ
    CHECK(hr);
}

void Graphics::Resize(float width, float height)
{
    DeleteSurface();    // �ʱ�ȭ
    {
        HRESULT hr = swapChain->ResizeBuffers   // ũ�� ������, 0 = ������ ������ ��, �̿��� �� : �ش� ������ ���� ����
        (
            0,
            (UINT)gWinWidth,
            (UINT)gWinHeight,
            DXGI_FORMAT_UNKNOWN,    // 0, �������� ���ؼ� ���
            0
        );
        CHECK(hr);
    }
    CreateRenderTargetView();
    SetViewport(width, height);

    cout << width << " X " << height << '\n';
}

void Graphics::SetViewport(float width, float height)
{
    viewport.TopLeftX = 0.0f;
    viewport.TopLeftY = 0.0f;
    viewport.Width = width;
    viewport.Height = height;
    viewport.MinDepth = 0.0f;  // 2D �����̶�, 0~1�� �⺻ �����̴�.
    viewport.MaxDepth = 1.0f;
}

void Graphics::SetViewport()
{
    // RS �ܰ迡�� ��ǥƮ ��ȯ ����
    deviceContext->RSSetViewports(1, &viewport);
}

void Graphics::SetBackBufferToRTV()
{
    // OM �ܰ迡�� ��ȭ�� ����, �׸� ��� ����
    deviceContext->OMSetRenderTargets(1, rtv.GetAddressOf(), nullptr);
    // �� �����ӿ� ������Ʈ �Ǳ� ������ �⺻������ �ʱ�ȭ
    deviceContext->ClearRenderTargetView(rtv.Get(), clearColor);
}

bool Graphics::GetFullScreenState()
{
    BOOL bFullScreen = false;
    swapChain->GetFullscreenState(&bFullScreen, nullptr);

    return bFullScreen;
}

void Graphics::SetFullScreenState(bool bFullScreen)
{
    swapChain->SetFullscreenState(bFullScreen, nullptr);
    Resize(gWinWidth, gWinHeight);
}

void Graphics::EnumerateAdapters()
{
    ComPtr<IDXGIFactory1> factory;  // �ڿ� �ٴ� ���ڴ� ������ �ǹ�

    HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), &factory);
    CHECK(hr);

    UINT index = 0;
    while (true)
    {
        ComPtr<IDXGIAdapter1> adapter;

        HRESULT hr = factory->EnumAdapters1(index, &adapter);   // ������ factory�� ���ؼ� index�� �־� adapter�� �޾ƿ´�.

        if (hr == DXGI_ERROR_NOT_FOUND)  // ��͸� ��ã�� ����� ����
            break;  // index�� �´� ��Ͱ� ���� ��� Ż��

        CHECK(hr);

        auto adapterInfo = make_shared<D3DEnumAdapterInfo>();
        adapterInfo->adapterOrdinal = index;

        hr = adapter->GetDesc1(&adapterInfo->adapterDesc);
        CHECK(hr);
        adapterInfo->adapter = adapter;

        EnumerateAdapterOutput(adapterInfo);
        adapterInfos.push_back(adapterInfo);

        ++index;
    }
}

bool Graphics::EnumerateAdapterOutput(const shared_ptr<D3DEnumAdapterInfo>& adapterInfo)
{
    ComPtr<IDXGIOutput> outputBase;
    
    HRESULT hr = adapterInfo->adapter->EnumOutputs(0, &outputBase);

    if (hr == DXGI_ERROR_NOT_FOUND)
        return false;

    ComPtr<IDXGIOutput1> output;

    outputBase->QueryInterface<IDXGIOutput1>(&output);

    auto outputInfo = make_shared<D3DEnumOutputInfo>();

    hr = output->GetDesc(&outputInfo->outputDesc);
    CHECK(hr);

    outputInfo->output = output;

    UINT numModes = 0;
    vector<DXGI_MODE_DESC1> displayModes;
    DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

    hr = output->GetDisplayModeList1(format, 0, &numModes, nullptr);
    CHECK(hr);

    displayModes.assign(numModes, DXGI_MODE_DESC1());
    hr = output->GetDisplayModeList1(format, 0, &numModes, displayModes.data());
    CHECK(hr);

    for (const auto& mode : displayModes)
    {
        resolutionList.push_back(Vector3((float)mode.Width, (float)mode.Height, (float)mode.RefreshRate.Numerator /mode.RefreshRate.Denominator));

        if (mode.Width == WIN_DEFAULT_WIDTH && mode.Height == WIN_DEFAULT_HEIGHT)
        {
            outputInfo->numerator = mode.RefreshRate.Numerator;
            outputInfo->denominator = mode.RefreshRate.Denominator;
        }
    }

    for (const auto& res : resolutionList)
        cout << res.x << " X " << res.y << " (" << res.z << ")" << '\n';

    adapterInfo->outputInfo = outputInfo;

    return true;
}

void Graphics::CreateSwapChain()
{
    DXGI_SWAP_CHAIN_DESC desc = { 0 };
    //	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));	// �ʱ�ȭ

    desc.BufferDesc.Width = 0;
    desc.BufferDesc.Height = 0;

    UINT maxVideoMemory = 0;
    for (UINT i = 0; i < adapterInfos.size(); ++i)
    {
        if (adapterInfos[i]->adapterDesc.DedicatedVideoMemory > maxVideoMemory)  // ���� �޸𸮰� ū ���, ���� �׷��� ī��
        {
            selectedAdapterIndex = i;
            maxVideoMemory = (UINT)adapterInfos[i]->adapterDesc.DedicatedVideoMemory;
        }
    }

    const auto& adapterInfo = adapterInfos[0];

    numerator = adapterInfo->outputInfo->numerator;
    denominator = adapterInfo->outputInfo->denominator;

    if (bVsync)
    {
        desc.BufferDesc.RefreshRate.Numerator = numerator;
        desc.BufferDesc.RefreshRate.Denominator = denominator;
    }
    else
    {
        desc.BufferDesc.RefreshRate.Numerator = 0;  // ���� / ���� 0�϶� ������ ���� X
        desc.BufferDesc.RefreshRate.Denominator = 1;
    }
    
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // ��Ÿ�� ȭ�� �� ä�δ� ������ �󸶳� �Ҵ��� ������ , R8G8B8A8_UNORM
    desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;

    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // buffer�� � �뵵�� ���� ������

    desc.BufferCount = 1;   // ������ ����, backBuffer�� �ϳ������� 1��

    desc.OutputWindow = gHandle;    // ��� ������â�� �ڵ��� �޴´�.

    desc.Windowed = true;   // â ��� ����� ������

    desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // backBuffer�� frontBuffer�� swap�� �Ҷ� ��� ȿ���� �߰��� �� �ִ�, �⺻������ �ƹ� ȿ���� ����.

    vector<D3D_FEATURE_LEVEL> featureLevel
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1, // �ش� ��ǻ�Ϳ��� 11������ �ȵ� ��� ������ ������ ��밡���� ������ ���
        D3D_FEATURE_LEVEL_10_0
    };

    D3D_FEATURE_LEVEL currentFeature;

    // ��ü ���� ��û
    HRESULT hr = D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,   // ���� ���߿� ���� ���̴� �ɼ�
        nullptr,
        0,
        featureLevel.data(),
        (UINT)featureLevel.size(),
        D3D11_SDK_VERSION,
        &desc,
        &swapChain, // & : �̹� �Ҵ�� �ڿ��� ������ �Ǹ�, �ش� ����Ʈ ������ ��ü�� ������ �´�.
        &device,
        &currentFeature,    // ���� �ý����� ����ϰ� �ִ� Level�� ����ش�.
        &deviceContext
    );

    CHECK(hr);  // hr�� SUCCEEDED�� ��� �������� assert ���

    gpuMemorySize = maxVideoMemory / 1024 / 1024;
    gpuDescription = adapterInfos[selectedAdapterIndex]->adapterDesc.Description;

    cout << '\n' << "DedicatedVideoMemory : " << gpuMemorySize << '\n';
    wcout << "GPU Description : " << gpuDescription << '\n';

    cout << "Numerator : " << numerator << '\n';
    cout << "Denominator : " << denominator << '\n';
    cout << "RefreshRate : " << numerator / denominator << "\n\n";

    Resize(WIN_DEFAULT_WIDTH, WIN_DEFAULT_HEIGHT);
}

void Graphics::CreateRenderTargetView()
{
    // ����۴� Texture2D�� ���°� �� �����ϴ�.
    ComPtr<ID3D11Texture2D> backBuffer;
    // ����ü�����κ��� ����۸� �޾ƿ��� �Լ�
    HRESULT hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);  // ���° ����, __uuidof : �������̽��� ���̵� ���� �����´�., ǥ��
    CHECK(hr);

    // �ڿ����� ����
    hr = device->CreateRenderTargetView
    (
        backBuffer.Get(),
        nullptr,    // swapChain�� GetBuffer �Լ��� ���� �ʿ��� ������ ����ִ� �ڿ��� �ֱ� ������
        &rtv
    );
    CHECK(hr);
}

void Graphics::DeleteSurface()  // RTV�� ������ ����
{
    rtv.Reset();
}
