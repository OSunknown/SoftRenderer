#include "stdafx.h"
#include "Vector.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Triangle.h"
#include "Texture.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Material.h"
bool IsInRange(int x, int y);
void PutPixel(IntPoint pt)
{
	if (!IsInRange(pt.X, pt.Y)) return;

	ULONG* dest = (ULONG*)g_pBits;

	int halfWidth = RoundToInt(g_nClientWidth * 0.5f);
	int halfHeight = RoundToInt(g_nClientHeight * 0.5f);

	DWORD offset = (halfHeight * g_nClientWidth - g_nClientWidth * pt.Y) + (halfWidth + pt.X);
	*(dest + offset) = g_CurrentColor;
}

bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}


Vertex VertexShader(Vertex in)
{
	Vertex result;
	result.position = in.position;// TRS Matrix 반영해서 변환된 position 돌려주기..
	result.uv = in.uv;
	result.color = in.color;
	return result;
}

V2F_CUSTOM VertexShader(APPDATA_CUSTOM in)
{
	// TRS Matrix 반영해서 변환된 position 돌려주기..
	return V2F_CUSTOM();
}

ULONG FragmentShader(V2F_CUSTOM in, float s, float t)
{
	// Texture에서 색상 빼오기..
	if (g_Texture->IsLoaded())
	{
		return g_Texture->TextureSample(in.uv, s, t);
	}

	return in.color;
}


void DrawLine(const Vector3& start, const Vector3& end)
{
	float length = (end - start).Dist();
	float inc = 1.0f / length;

	int maxLength = RoundToInt(length);
	for (int i = 0; i <= maxLength; i++)
	{
		float t = inc * i;
		if (t >= length) t = 1.0f;
		Vector3 Pt = start * (1.0f - t) + end * t;
		PutPixel(Pt.ToIntPoint());
	}

}

void Draw2DTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{
	float xMin, yMin;
	float xMax, yMax;
	xMin = yMin = INFINITY;
	xMax = yMax = -INFINITY;

	if (v1.X < xMin) xMin = v1.X;
	if (v2.X < xMin) xMin = v2.X;
	if (v3.X < xMin) xMin = v3.X;
	if (v1.X > xMax) xMax = v1.X;
	if (v2.X > xMax) xMax = v2.X;
	if (v3.X > xMax) xMax = v3.X;
	if (v1.Y < yMin) yMin = v1.Y;
	if (v2.Y < yMin) yMin = v2.Y;
	if (v3.Y < yMin) yMin = v3.Y;
	if (v1.Y > yMax) yMax = v1.Y;
	if (v2.Y > yMax) yMax = v2.Y;
	if (v3.Y > yMax) yMax = v3.Y;

	Vector2 u = (v2 - v1).ToVector2();
	Vector2 v = (v3 - v1).ToVector2();
	float dotUU = u.Dot(u);
	float dotUV = u.Dot(v);
	float dotVV = v.Dot(v);
	float invDenom = 1.0f / (dotUU * dotVV - dotUV * dotUV);

	for (int y = RoundToInt(yMin); y < RoundToInt(yMax); y++)
	{
		for (int x = RoundToInt(xMin); x < RoundToInt(xMax); x++)
		{
			Vector2 w = (Vector3((float)x, (float)y, 0.0f) - v1).ToVector2();
			float dotUW = u.Dot(w);
			float dotVW = v.Dot(w);
			float outS = (dotVV * dotUW - dotUV * dotVW) * invDenom;
			float outT = (dotUU * dotVW - dotUV * dotUW) * invDenom;
			if (outS < 0.0f) continue;
			if (outT < 0.0f) continue;
			if (outS + outT > 1.0f) continue;

			PutPixel(IntPoint(x, y));
		}
	}

	

	
}/*

void Draw2DTriangle(Triangle tri)
{
	for (int y = RoundToInt(tri.yMin); y < RoundToInt(tri.yMax); y++)
	{
		for (int x = RoundToInt(tri.xMin); x < RoundToInt(tri.xMax); x++)
		{
			if (tri.IsInTriangle(x, y))
			{
				g_CurrentColor = (tri.GetColor(x,y));
				PutPixel(IntPoint(x, y));
			}
		}
	}
}*/


void Draw2DMesh(Mesh mesh)
{
	
}


void InitFrame(void)
{
}

void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	// Draw
	Vector3 Pt1, Pt2, Pt3, Pt4;

	static float offsetX = 0.0f;
	//static float offsetY = 0.0f;
	static float angle = 0.0f;
	static float scale = 1.0f;

	if (GetAsyncKeyState(VK_LEFT)) offsetX -= 1.0f;
	if (GetAsyncKeyState(VK_RIGHT)) offsetX += 1.0f;
	if (GetAsyncKeyState(VK_UP)) angle += 1.0f;
	if (GetAsyncKeyState(VK_DOWN)) angle -= 1.0f;
	if (GetAsyncKeyState(VK_PRIOR)) scale *= 1.01f;
	if (GetAsyncKeyState(VK_NEXT)) scale *= 0.99f;

	Matrix3 TMat, RMat, SMat;
	TMat.SetTranslation(offsetX, 0.0f);
	RMat.SetRotation(angle);
	SMat.SetScale(scale);
	Matrix3 TRSMat = TMat * RMat * SMat;

	Sprite sp;

	Sprite sp2(Vector3(80,80,0),160,160);
	sp2.DrawCall(TRSMat);
	Material mat;
	mat.DrawCall(sp, TRSMat);

	//DrawCall(sp);
	
	//
	//Pt1.SetPoint(0.0f, 0.0f);
	//Pt2.SetPoint(160.0f, 160.0f);
	//Pt3.SetPoint(0.0f, 160.0f);
	//Pt4.SetPoint(160.0f, 0.0f);
	///*
	//SetColor(255, 0, 0);
	//Draw2DTriangle(Pt1 * TRSMat, Pt2 * TRSMat, Pt3 * TRSMat);
	//*/

	////
	///*Vertex v1(Pt1 * TRSMat, RGB(255, 0, 0));
	//Vertex v2(Pt2 * TRSMat, RGB(0, 255, 0));
	//Vertex v3(Pt3 * TRSMat, RGB(0, 0, 255));
	//Triangle tri(v1, v2, v3);
	//Draw2DTriangle(tri);*/

	//Vertex v[4] = {
	//	Vertex(Pt1 * TRSMat, RGB(255, 0, 0),Vector2(0.0f,1.0f)),
	//	Vertex(Pt2 * TRSMat, RGB(0, 255, 0),Vector2(1.0f,0.0f)),
	//	Vertex(Pt3 * TRSMat, RGB(0, 0, 255),Vector2(0.0f,0.0f)),
	//	Vertex(Pt4 * TRSMat, RGB(255, 255, 0),Vector2(1.0f,1.0f))
	//};
	//int index[6] = {
	//	0, 1, 2, 0, 1, 3
	//};
	//Mesh m(v,4);
	//m.SetIndex(index,6);
	//Draw2DMesh(m);

	//1. Mesh

	// Buffer Swap 
	BufferSwap();
}
