#include "stdafx.h"
#include "IShader.h"

void IShader::CompileShader(const wstring& path, const string& entryName, const string& profile, ID3DBlob** blob)
{
	ComPtr<ID3DBlob> error;

	HRESULT hr = D3DCompileFromFile
	(
		path.c_str(),
		nullptr,
		nullptr,
		entryName.c_str(),
		profile.c_str(),
		D3DCOMPILE_ENABLE_STRICTNESS,	// STRICTNESS : ������, ���Ž� ������ ������� ����
		0,
		blob,
		&error
	);

	CheckShaderError(hr, error);
}

void IShader::CheckShaderError(const HRESULT& hr, const ComPtr<ID3DBlob>& error)
{
	// hlsl�� ������ �ִ���, �����Ϸ��� ������ �ִ��� check
	if (FAILED(hr))	// ���� check
	{
		if (error.Get())	// ������ ������ �ִٸ�
		{
			const string& str = (const char*)error->GetBufferPointer();	// ���� ��ġ�� �������·� ����Ǿ� �ִ� �������� ��ġ�� const char*�� ����ȯ�� ����
			MessageBoxA(nullptr, str.c_str(), "Shader Error", MB_OK);
		}
		assert(false);
	}
}
