#pragma once

#include "stdafx.h"
#include "Vector.h"
#include "Vertex.h"

struct APPDATA_CUSTOM
{
	APPDATA_CUSTOM() {}
	~APPDATA_CUSTOM() {}
	Vector3 position;
	ULONG color;
	Vector2 uv;
};

struct V2F_CUSTOM
{
	Vector3 posiiton;
	Vector2 uv; //������ uv ��ǥ
	ULONG color; //������ ����
};


struct Triangle
{
public:
	Vertex vertices[3];
	float xMin, yMin;
	float xMax, yMax;
	Vector2 U, V, W;
	float invDenom;
public:
	Triangle() {
		xMin = yMin = INFINITY;
		xMax = yMax = -INFINITY;
	}

	Triangle(const Vector3& v1, const Vector3& v2, const Vector3& v3)
	{
		xMin = yMin = INFINITY;
		xMax = yMax = -INFINITY;
		SetPoint(v1);
		vertices[0] = Vertex(v1); //�� A
		SetPoint(v2);
		vertices[1] = Vertex(v2); //�� B
		SetPoint(v3);
		vertices[2] = Vertex(v3); //�� C

		U = (v2 - v1).ToVector2();
		V = (v3 - v1).ToVector2();
		invDenom = 1.0f/ (U.Dot(U) *V.Dot(V) - U.Dot(V) * V.Dot(U));
	}

	Triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
	{
		xMin = yMin = INFINITY;
		xMax = yMax = -INFINITY;

		SetPoint(v1.position);
		vertices[0] = v1; //�� A
		SetPoint(v2.position);
		vertices[1] = v2; //�� B
		SetPoint(v3.position);
		vertices[2] = v3; //�� C

		U = (v2.position - v1.position).ToVector2();
		V = (v3.position - v1.position).ToVector2();
		invDenom = 1.0f / (U.Dot(U) *V.Dot(V) - U.Dot(V) * V.Dot(U));
	}

	bool IsInTriangle(float X,float Y) { 
		//Point �� �� D
		W.X = X - vertices[0].position.X;
		W.Y = Y - vertices[0].position.Y;
		float s = ((V.Dot(V)*W.Dot(U)) - (V.Dot(U)*W.Dot(V))) * invDenom;
		float t = (U.Dot(U)*W.Dot(V) - U.Dot(V)*W.Dot(U)) * invDenom;
		
		if (s<0.0f || t <0.0f) //�̰� ������ �簢����..
		{
			return false;
		}
		else if (s + t <= 1)
		{
			return true;
		}
		
		return false;
	}

	ULONG GetColor(float X, float Y)
	{
		float s = ((V.Dot(V)*W.Dot(U)) - (V.Dot(U)*W.Dot(V))) * invDenom;
		float t = (U.Dot(U)*W.Dot(V) - U.Dot(V)*W.Dot(U)) * invDenom;

		BYTE RV0 = GetRValue(vertices[0].color) * (1.0f - s - t);
		BYTE GV0 = GetGValue(vertices[0].color) * (1.0f - s - t);
		BYTE BV0 = GetBValue(vertices[0].color) * (1.0f - s - t);

		BYTE RV1 = GetRValue(vertices[1].color) * s;
		BYTE GV1 = GetGValue(vertices[1].color) * s;
		BYTE BV1 = GetBValue(vertices[1].color) * s;

		BYTE RV2 = GetRValue(vertices[2].color) * t;
		BYTE GV2 = GetGValue(vertices[2].color) * t;
		BYTE BV2 = GetBValue(vertices[2].color) * t;

		BYTE R = RV0 + RV1 + RV2;
		BYTE G = GV0 + GV1 + GV2;
		BYTE B = BV0 + BV1 + BV2;

		return RGB(R,G,B);
	}
private:
	void SetPoint(const Vector3& point)
	{
		if (point.X < xMin) xMin = point.X;
		if (point.X > xMax) xMax = point.X;
		if (point.Y < yMin) yMin = point.Y;
		if (point.Y > yMax) yMax = point.Y;
	}
};
