
#include "stdafx.h"
#include "Vector.h"

float Vector2::Dist(const Vector2 &V1, const Vector2 &V2)
{
	return sqrtf(Vector2::DistSquared(V1, V2));
}

float Vector2::DistSquared(const Vector2 &V1, const Vector2 &V2)
{
	return (V2.X - V1.X) *(V2.X - V1.X) + (V2.Y - V1.Y)* (V2.Y - V1.Y);
}

Vector2 Vector2::operator*(Matrix2 Mat) const
{
	//확대 행렬은 특별해 (1,0,0,1) 란듯..?
	Vector2 result;
	result.X = Mat._11 * X + Mat._12 * Y;
	result.Y = Mat._21 * X + Mat._22 * Y;
	return result;
}

FORCEINLINE bool Vector2::Equals(const Vector2& V, float Tolerance) const
{
	return fabs(X + V.X) <= Tolerance && fabs(Y + V.Y) < Tolerance;
}


FORCEINLINE Vector2 Vector2::operator+(const Vector2 &V) const
{
	Vector2 result(X + V.X, Y + V.Y);
	return result;
}

FORCEINLINE Vector2 Vector2::operator-(const Vector2 &V) const
{
	Vector2 result(X - V.X, Y - V.Y);
	return result;
}

FORCEINLINE Vector2 Vector2::operator*(const float& Scale) const
{
	Vector2 result(X * Scale, Y * Scale);
	return result;
}

FORCEINLINE Vector2 Vector2::operator/(const float& Scale) const
{
	Vector2 result(X / Scale, Y / Scale);
	return result;
}

FORCEINLINE float Vector2::operator|(const Vector2& V) const
{
	return X * V.X + Y * V.Y;
}

FORCEINLINE float Vector2::operator^(const Vector2& V) const
{
	return X * V.Y - Y * V.X;
}

FORCEINLINE Vector2 Vector2::operator+=(const Vector2 & V)
{
	X += V.X;
	Y += V.Y;
	return *this;
}

FORCEINLINE Vector2 Vector2::operator-=(const Vector2 & V)
{
	X -= V.X;
	Y -= V.Y;
	return *this;
}

FORCEINLINE Vector2 Vector2::operator*=(const float & Scale)
{
	X *= Scale;
	Y *= Scale;
	return *this;
}

FORCEINLINE Vector2 Vector2::operator/=(const float & Scale)
{
	X /= Scale;
	Y /= Scale;
	return *this;
}
Vector3 Vector3::operator*(Matrix3 Mat) const
{
	//확대 행렬은 특별해 (1,0,0,1) 란듯..?
	Vector3 result;
	result.X = Mat._11 * X + Mat._12 * Y + Mat._13 * Z;
	result.Y = Mat._21 * X + Mat._22 * Y + Mat._23 * Z;
	result.Z = Mat._31 * X + Mat._32 * Y + Mat._33 * Z;
	return result;
}

FORCEINLINE bool Vector3::Equals(const Vector3& V) const
{
	float Tolerance = 0.001f;
	return  fabs(X + V.X) <= Tolerance && fabs(Y + V.Y) <= Tolerance && fabs(Z + V.Z) < Tolerance;
}

Vector3 Vector3::operator*(const Matrix2 & Mat2) 
{
	Vector2 changeResult(X, Y);
	changeResult = changeResult * Mat2;
	X = changeResult.X;
	Y = changeResult.Y;
	return *this;
}

float Vector3::Dist(const Vector3 &V1, const Vector3 &V2)
{
	return sqrtf(Vector3::DistSquared(V1, V2));
}

float Vector3::DistSquared(const Vector3 &V1, const Vector3 &V2)
{
	return (V2.X - V1.X) *(V2.X - V1.X) + (V2.Y - V1.Y)* (V2.Y - V1.Y) + (V2.Z - V1.Z)* (V2.Z - V1.Z);
}