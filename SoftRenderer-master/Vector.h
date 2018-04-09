#pragma once

#include "stdafx.h"
#include "Matrix.h"

struct Vector2
{
public:
	float X;
	float Y;
public:
	Vector2() : X(0), Y(0) {}
	Vector2(float InX, float InY) : X(InX), Y(InY) {}
	void SetPoint(float InX, float InY)
	{
		X = InX;
		Y = InY;
	}
	static float Dist(const Vector2 &V1,const Vector2 &V2);
	static float DistSquared(const Vector2 &V1, const Vector2 &V2);
	Vector2 operator *(const Matrix2 Mat) const;
	FORCEINLINE bool Vector2::Equals(const Vector2& V, float Tolerance) const;

	FORCEINLINE Vector2 operator+(const Vector2 &V) const;
	FORCEINLINE Vector2 operator-(const Vector2 &V) const;
	FORCEINLINE Vector2 operator*(const float &Scale) const;
	FORCEINLINE Vector2 operator/(const float &Scale) const;

	FORCEINLINE float operator|(const Vector2 &V) const;
	FORCEINLINE float operator^(const Vector2 &V) const;

	FORCEINLINE Vector2 operator+=(const Vector2 &V);
	FORCEINLINE Vector2 operator-=(const Vector2 &V);
	FORCEINLINE Vector2 operator*=(const float &Scale);
	FORCEINLINE Vector2 operator/=(const float &Scale);
};


struct Vector3
{
public:
	float X;
	float Y;
	float Z;
public:
	Vector3() : X(0), Y(0), Z(0){}
	Vector3(float InX, float InY,float InZ) : X(InX), Y(InY), Z(InZ){}
	
	void SetPoint(float InX, float InY)
	{
		X = InX;
		Y = InY;
		Z = 1.0f;
	}

	void SetVector(float InX, float InY)
	{
		X = InX;
		Y = InY;
		Z = 0.0f;
	}

	Vector3 operator *(const Matrix3 Mat) const;

	Vector3 Zero()
	{
		Vector3 result(0.0f, 0.0f, 0.0f);
		return result;
	}

	bool ZeroCheck()
	{
		return (X == 0.0f && Y == 0.0f && Z == 0.0f);
	}

	FORCEINLINE bool Vector3::Equals(const Vector3& V) const;
	Vector3 operator*(const Matrix2 &Mat2);
	static float Dist(const Vector3 & V1, const Vector3 & V2);
	static float DistSquared(const Vector3 & V1, const Vector3 & V2);
};