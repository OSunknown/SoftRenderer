
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