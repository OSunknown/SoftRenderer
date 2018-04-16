#pragma once

#include "stdafx.h"
#include "Vector.h"

struct Vertex
{
public:
	Vertex() {}
	Vertex(const Vector3& v) {
		position = v;
	}
	Vector3 position;
	ULONG color;
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
		vertices[0] = Vertex(v1); //점 A
		SetPoint(v2);
		vertices[1] = Vertex(v2); //점 B
		SetPoint(v3);
		vertices[2] = Vertex(v3); //점 C

		U = (v2 - v1).ToVector2();
		V = (v3 - v1).ToVector2();
		invDenom = 1.0f/ (U.Dot(U) *V.Dot(V) - U.Dot(V) * V.Dot(U));
	}

	bool IsInTriangle(float X,float Y) { 
		//Point 가 점 D
		W.X = X - vertices[0].position.X;
		W.Y = Y - vertices[0].position.Y;
		float s = ((V.Dot(V)*W.Dot(U)) - (V.Dot(U)*W.Dot(V))) * invDenom;
		float t = (U.Dot(U)*W.Dot(V) - U.Dot(V)*W.Dot(U)) * invDenom;
		
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
private:
	void SetPoint(const Vector3& point)
	{
		if (point.X < xMin) xMin = point.X;
		if (point.X > xMax) xMax = point.X;
		if (point.Y < yMin) yMin = point.Y;
		if (point.Y > yMax) yMax = point.Y;
	}
};

