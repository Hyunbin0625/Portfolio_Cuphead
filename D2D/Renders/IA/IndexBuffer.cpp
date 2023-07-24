#include "stdafx.h"
#include "IndexBuffer.h"

void IndexBuffer::Create(const vector<UINT>& indices, const D3D11_USAGE& usage)
{
	stride = sizeof(UINT);	// stride : ����
	count = (UINT)indices.size();

	D3D11_BUFFER_DESC desc = { 0 };
	desc.ByteWidth = stride * count;			// ���� ���� �� ����Ʈ ��, ��ü ũ��
	desc.Usage = usage;							// � �뵵�� Ȱ���� ������
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;	// ��� � �뵵�� ���ε��� ������

	switch (usage)
	{
	case D3D11_USAGE_DEFAULT:
		break;
	case D3D11_USAGE_IMMUTABLE:
		desc.CPUAccessFlags = 0;
		break;
	case D3D11_USAGE_DYNAMIC:
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case D3D11_USAGE_STAGING:
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		break;
	}

	D3D11_SUBRESOURCE_DATA subData = { 0 };
	subData.pSysMem = indices.data();

	HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);
	CHECK(hr);
}

void IndexBuffer::SetIA()
{
	DC->IASetIndexBuffer(buffer.Get(), DXGI_FORMAT_R32_UINT, offset);
}
