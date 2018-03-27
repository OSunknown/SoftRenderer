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
