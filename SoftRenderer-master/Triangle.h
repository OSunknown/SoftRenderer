#pragma once

#include "stdafx.h"
#include "Vector.h"
#include "Vertex.h"

struct APPDATA_CUSTOM
{
	APPDATA_CUSTOM() {}
	~APPDATA_CUSTOM() {}
	Vector3 position;
	Vector2 uv;
	ULONG color;
};

struct V2F_CUSTOM
{
	Vector3 position;
	Vector2 uv; //보간된 uv 좌표
	ULONG color; //보간된 색상
};


struct Triangle
{
public:
	Vertex vt[3];
	float xMin, yMin;
	float xMax, yMax;
	Vector2 U, V, W;
	float invDenom;
	float s, t;
public:
	Triangle() {
		xMin = yMin = INFINITY;
		xMax = yMax = -INFINITY;
	}
	
	Triangle(const Vertex v1, const Vertex v2, const Vertex v3)
	{
		xMin = yMin = INFINITY;
		xMax = yMax = -INFINITY;
		SetPoint(v1);
		vt[0] = v1; //점 A
		SetPoint(v2);
		vt[1] = v2; //점 B
		SetPoint(v3);
		vt[2] = v3; //점 C

		U = (v2.position - v1.position).ToVector2();
		V = (v3.position - v1.position).ToVector2();
		invDenom = 1.0f / (U.Dot(U) *V.Dot(V) - U.Dot(V) * V.Dot(U));
	}


	bool IsInTriangle(float X,float Y) { 
		//Point 가 점 D
		W.X = X - vt[0].position.X;
		W.Y = Y - vt[0].position.Y;
		s = ((V.Dot(V)*W.Dot(U)) - (V.Dot(U)*W.Dot(V))) * invDenom;
		t = (U.Dot(U)*W.Dot(V) - U.Dot(V)*W.Dot(U)) * invDenom;
		
		if (s<0.0f || t <0.0f) //이거 없으면 사각형됨..
		{
			return false;
		}
		else if (s + t <= 1)
		{
			return true;
		}
		
		return false;
	}

	Vector2 GetUV()
	{
		Vector2 UV0 = vt[0].uv;
		Vector2 UV0ToUV1 = vt[1].uv - vt[0].uv;
		Vector2 UV0ToUV2 = vt[2].uv - vt[0].uv;
		Vector2 UVResult = UV0 + UV0ToUV1 * s + UV0ToUV2 * t;
		return UVResult;
	}
	

	ULONG GetColor(float X, float Y)
	{
//		s = ((V.Dot(V)*W.Dot(U)) - (V.Dot(U)*W.Dot(V))) * invDenom;
//		t = (U.Dot(U)*W.Dot(V) - U.Dot(V)*W.Dot(U)) * invDenom;

		BYTE RV0 = GetRValue(vt[0].color) * (1.0f - s - t);
		BYTE GV0 = GetGValue(vt[0].color) * (1.0f - s - t);
		BYTE BV0 = GetBValue(vt[0].color) * (1.0f - s - t);

		BYTE RV1 = GetRValue(vt[1].color) * s;
		BYTE GV1 = GetGValue(vt[1].color) * s;
		BYTE BV1 = GetBValue(vt[1].color) * s;

		BYTE RV2 = GetRValue(vt[2].color) * t;
		BYTE GV2 = GetGValue(vt[2].color) * t;
		BYTE BV2 = GetBValue(vt[2].color) * t;

		BYTE R = RV0 + RV1 + RV2;
		BYTE G = GV0 + GV1 + GV2;
		BYTE B = BV0 + BV1 + BV2;

		return RGB(R,G,B);
	}
private:
	void SetPoint(const Vertex& point)
	{
		if (point.position.X < xMin) xMin = point.position.X;
		if (point.position.X > xMax) xMax = point.position.X;
		if (point.position.Y < yMin) yMin = point.position.Y;
		if (point.position.Y > yMax) yMax = point.position.Y;
	}
};
