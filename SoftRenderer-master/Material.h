#pragma once
#include "Vector.h"
#include "Shader.h"
#include "Sprite.h"
#include "Texture.h"
#include "GDIHelper.h"
#include "SoftRenderer.h"
class Material
{

public:
	Material();
	~Material();
private:
	void init()
	{

	}
public:
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

	void DrawCall(Sprite sprite ,Matrix3 mat)
	{/*
		Texture * texture = new Texture();
		texture-> LoadBMP("test.bmp");*/
		TextureShader ts = TextureShader(mat, mat, mat);
		ts.SetTexcoord0(g_Texture);
		
		Mesh * mesh = sprite.mesh;
		Vertex * vt = mesh->Vertices;
		
		for (int i = 0; i < mesh->ISize; i++)
		{
			int a = mesh->Indices[i];
			int b = mesh->Indices[++i];
			int c = mesh->Indices[++i];

			Vertex va = vt[a];
			va.position = (va.position - sprite.position) * mat;
			va.position = va.position + sprite.position;
			Vertex vb = vt[b];
			vb.position = (vb.position - sprite.position) * mat;
			vb.position = vb.position + sprite.position;
			Vertex vc = vt[c];
			vc.position = (vc.position - sprite.position) * mat;
			vc.position = vc.position + sprite.position;
			Triangle tri(va, vb, vc);

			for (int y = tri.yMin; y <= tri.yMax; y++)
			{
				for (int x = tri.xMin; x <= tri.xMax; x++)
				{
					if (tri.IsInTriangle(x + 0.5f, y + 0.5f))
					{
						Vertex pixel;
						pixel.position = Vector3(x, y, sprite.z);
						pixel.uv = tri.GetUV();
						pixel.color = tri.GetColor(x, y);
						g_CurrentColor = ts.PixelShader(ts.VertexShader(ts.vInput(pixel)));
						PutPixel(IntPoint(x, y));
					}
				}
			}
		}
		delete[] vt;
	}
};

