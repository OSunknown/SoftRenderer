#pragma once
#include "stdafx.h"
#include "Mesh.h"
#include "Triangle.h"
#include "GDIHelper.h"
#include "SoftRenderer.h"
#include "Matrix.h"
struct Sprite
{
public:
	Vector3 position;
	Mesh* mesh;
	int z;
public:
	Sprite()
	{
		spriteInit();
	}
	Sprite(Vector3 Inposition, int width, int height)
	{
		spriteInit(Inposition, width, height);
	}
	~Sprite() {};
public:
	void spriteInit()
	{
		spriteInit(Vector3(0, 0, 0), 160, 160);
	}
	void spriteInit(Vector3 Inposition, int width, int height)
	{
		//메쉬 만듬 어짜피 사각형.
		mesh = new Mesh();
		position = Inposition;
		z = position.Z;
		float halfWidth = width * 0.5f;
		float halfHeight = height * 0.5f;
		
		Vertex * vt = new Vertex[4];
		vt[0] = Vertex(Vector3(-halfWidth + position.X, -halfHeight + position.Y, 0), RGB(255, 0, 0), Vector2(0.125f, 0.25f)); //왼쪽 아래
		vt[1] = Vertex(Vector3(halfWidth + position.X, halfHeight + position.Y, 0), RGB(0, 255, 0), Vector2(0.25f, 0.125f)); //오른쪽 위
		vt[2] = Vertex(Vector3(-halfWidth + position.X, halfHeight + position.Y, 0), RGB(0, 0, 255), Vector2(0.125, 0.125f)); //왼쪽 위
		vt[3] = Vertex(Vector3(halfWidth + position.X, -halfHeight + position.Y, 0), RGB(255, 255, 0), Vector2(0.25f, 0.25f)); //오른쪽 아래
		mesh->SetVertices(vt, 4);

		unsigned int *index = new unsigned int[6];
		index[0] = 0;
		index[1] = 1;
		index[2] = 2;
		index[3] = 0;
		index[4] = 1;
		index[5] = 3;
		mesh->SetIndices(index, 6);
	}
public:
	void SetVertexColor(Vector3 LeftDown, Vector3 LeftUp, Vector3 RightDown, Vector3 RightUp)
	{
		mesh->Vertices[0].color = RGB(LeftDown.X, LeftDown.Y, LeftDown.Z);
		mesh->Vertices[1].color = RGB(RightUp.X, RightUp.Y, RightUp.Z);
		mesh->Vertices[2].color = RGB(LeftUp.X, LeftUp.Y, LeftUp.Z);
		mesh->Vertices[3].color = RGB(RightDown.X, RightDown.Y, RightDown.Z);
	}

	bool IsInRange(int x, int y)
	{
		return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
	}

	void PutPixel(IntPoint pt)
	{
		if (!IsInRange(pt.X, pt.Y)) return;

		ULONG* dest = (ULONG*)g_pBits;

		int halfWidth = RoundToInt(g_nClientWidth * 0.5f);
		int halfHeight = RoundToInt(g_nClientHeight * 0.5f);

		DWORD offset = (halfHeight * g_nClientWidth - g_nClientWidth * pt.Y) + (halfWidth + pt.X);
		*(dest + offset) = g_CurrentColor;
	}

	void DrawCall(Matrix3 mat)
	{
		Vertex * vt = mesh->Vertices;
		for (int i = 0; i < mesh->ISize; i++)
		{
			int a = mesh->Indices[i];
			int b = mesh->Indices[++i];
			int c = mesh->Indices[++i];
			Vertex va = vt[a];
			va.position = (va.position - position) * mat;
			va.position = va.position + position;
			Vertex vb = vt[b];
			vb.position = (vb.position - position) * mat;
			vb.position = vb.position + position;
			Vertex vc = vt[c];
			vc.position = (vc.position - position) * mat;
			vc.position = vc.position + position;
			Triangle tri(va,vb,vc);

			for (int y = tri.yMin; y <= tri.yMax; y++)
			{
				for (int x = tri.xMin; x <= tri.xMax; x++)
				{
					if (tri.IsInTriangle(x + 0.5f, y + 0.5f))
					{
						g_CurrentColor = tri.GetColor(x, y);
						if (g_Texture->IsLoaded())
						{
							g_CurrentColor = g_Texture->GetTexturePixel(tri.s, tri.t, tri);
						}
						else
						{
							g_CurrentColor = (tri.GetColor(x, y));
						}
						PutPixel(IntPoint(x, y));
					}
				}
			}
		}
	}
};

