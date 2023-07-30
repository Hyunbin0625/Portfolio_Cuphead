#pragma once

#include "stdafx.h"

class WorldBuffer : public ConstantBuffer
{
	struct WorldStruct
	{
		Matrix world;	// 16 ����� �ؾ��Ѵ�. ����Ʈ �е�
	};

public:
	WorldBuffer() : ConstantBuffer(&data, sizeof(data)) {}

	void SetWorld(const Matrix& world)
	{
		data.world = XMMatrixTranspose(world);	// ��ġ ����� ���� ���켱 ��ķ� ���� �� �ѱ��.
	}

private:
	WorldStruct data;
};

class ViewProjectionBuffer : public ConstantBuffer
{
	struct ViewProjectionStruct
	{
		Matrix view;
		Matrix projection;	// 16 ����� �ؾ��Ѵ�. ����Ʈ �е�
	};

public:
	ViewProjectionBuffer() : ConstantBuffer(&data, sizeof(data)) {}

	void SetView(const Matrix& view)
	{
		data.view = XMMatrixTranspose(view);	// ��ġ ����� ���� ���켱 ��ķ� ���� �� �ѱ��.
	}

	void SetProjection(const Matrix& projection)
	{
		data.projection = XMMatrixTranspose(projection);	// ��ġ ����� ���� ���켱 ��ķ� ���� �� �ѱ��.
	}

private:
	ViewProjectionStruct data;
};

class ColorBuffer : public ConstantBuffer
{
	struct ColorStruct
	{
		Color color;	// 16 ����� �ؾ��Ѵ�. ����Ʈ �е�
	};

public:
	ColorBuffer() : ConstantBuffer(&data, sizeof(data)) {}

	void SetColor(const Color& color)
	{
		data.color = color;
	}

private:
	ColorStruct data;
};

class SelectionBuffer : public ConstantBuffer
{
	struct SelectionStruct
	{
		UINT selection = 1;	// 16 ����� �ؾ��Ѵ�. ����Ʈ �е�
		Vector3 dummy;
	};

public:
	SelectionBuffer() : ConstantBuffer(&data, sizeof(data)) {}

	void SetSelection(const UINT& selection)
	{
		data.selection = selection;
	}

private:
	SelectionStruct data;
};

class OutlineBuffer : public ConstantBuffer
{
	struct OutlineStruct
	{
		bool bOutline = false;	// 16 ����� �ؾ��Ѵ�. ����Ʈ �е�
		char dumy;
		short dumy1;
		Vector3 dummy2;
	};

public:
	OutlineBuffer() : ConstantBuffer(&data, sizeof(data)) {}

	void SetOutline(const bool& bOutline)
	{
		data.bOutline = bOutline;
	}

private:
	OutlineStruct data;
};