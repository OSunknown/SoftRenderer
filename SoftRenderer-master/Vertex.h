#pragma once
#include "Vector.h"

struct Vertex
{
public:
	Vertex() {}
	Vertex(const Vector3& v) {
		position = v;
	}
	Vertex(const Vector3& v, ULONG c)
	{
		position = v;
		color = c;
	}
	Vertex(const Vector3& v, ULONG c, Vector2 InUV)
	{
		position = v;
		color = c;
		uv = InUV;
	}
	Vertex(const Vertex* vertex)
	{
		position = vertex->position;
		color = vertex->color;
		uv = vertex->uv;
	}
	Vector3 position;
	ULONG color;
	Vector2 uv;
};

// Render Queue �� ���� ���� ���� �׷�����
// ���� ���� ���߿� �׷������� ���ؼ�
//

//ZBuffer �� ���̰�.?