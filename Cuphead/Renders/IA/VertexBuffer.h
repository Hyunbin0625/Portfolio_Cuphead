#pragma once

class VertexBuffer
{
public:
	template<typename T>	// �Լ����ø�
	void Create(const vector<T>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

	ID3D11Buffer* GetResource() const { return buffer.Get(); }
	UINT GetStride() const { return stride; }
	UINT GetOffset() const { return offset; }
	UINT GetCount() const { return count; }

	void SetIA();	// Render���� �ϴ� Set

private:
	ComPtr<ID3D11Buffer> buffer;
	UINT stride = 0;
	UINT offset = 0;
	UINT count = 0;
};

template<typename T>
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE& usage)
{
	stride = sizeof(T);	// stride : ����
	count = (UINT)vertices.size();

	D3D11_BUFFER_DESC desc = { 0 };
	desc.ByteWidth = stride * count;			// ���� ���� �� ����Ʈ ��, ��ü ũ��
	desc.Usage = usage;							// � �뵵�� Ȱ���� ������
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ��� � �뵵�� ���ε��� ������

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
	subData.pSysMem = vertices.data();

	HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);
	CHECK(hr);
}
