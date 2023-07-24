#include "stdafx.h"
#include "InputLayout.h"

void InputLayout::Create(const vector<D3D11_INPUT_ELEMENT_DESC> desc, const ComPtr<ID3DBlob>& blob)
{
	if (desc.empty() || !blob.Get())	// ����ִ� ��� �Ǵ� blob�� null�� ���
		assert(false);

	HRESULT hr = DEVICE->CreateInputLayout
	(
		desc.data(),
		(UINT)desc.size(),
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&inputLayout
	);
	CHECK(hr);
}

void InputLayout::SetIA()
{
	DC->IASetInputLayout(inputLayout.Get());
}
