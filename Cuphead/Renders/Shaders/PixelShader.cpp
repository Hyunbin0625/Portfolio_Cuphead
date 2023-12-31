#include "stdafx.h"
#include "PixelShader.h"

void PixelShader::Create(const wstring& path, const string& entryName)
{
	this->path = path;
	this->entryName = entryName;

	CompileShader(path, entryName, "ps_5_0", &blob);

	HRESULT hr = DEVICE->CreatePixelShader
	(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&shader
	);
	CHECK(hr);
}

void PixelShader::Clear()
{
	shader.Reset();
	blob.Reset();
}

void PixelShader::SetShader()
{
	DC->PSSetShader(shader.Get(), nullptr, 0);
}
