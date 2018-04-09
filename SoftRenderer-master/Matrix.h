#pragma once

#include "stdafx.h"



struct Matrix2
{
public :
	float _11, _12;
	float _21, _22;
	Matrix2() {};
	Matrix2(float m11, float m12, float m21, float m22)
	{
		_11 = m11;
		_12 = m12;
		_21 = m21;
		_22 = m22;
	};

	void SetScale(float a, float b) //스케일
	{
		SetIdentity();
		_11 = a;
		_22 = b;
	}

	void SetIdentity() //항등
	{
		_11 = 1.0f;
		_12 = 0.0f;
		_21 = 0.0f;
		_22 = 1.0f;
	};

	void SetRotation(float degree) //회전
	{
		float rad = Deg2Rad(degree);
		_11 = cosf(rad);
		_12 = -sinf(rad);
		_21 = sinf(rad);
		_22 = cosf(rad);
	}

	void SetShear(float shx,float shy)
	{
		SetIdentity();
		_12 = shx;
		_21 = shy;
	}

	void SetMirror()
	{
		SetIdentity();
		_11 = -1;
	}

	void SetReflection()
	{
		SetIdentity();
		_11 = -1;
		_22 = -1;
	}
	Matrix2 operator *(const Matrix2 Other) const;
};


struct Matrix3
{
public:
	float _11, _12, _13;
	float _21, _22, _23;
	float _31, _32, _33;

	Matrix3() {};
	Matrix3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33 )
	{
		_11 = m11;
		_12 = m12;
		_13 = m13;
		_21 = m21;
		_22 = m22;
		_23 = m23;
		_31 = m31;
		_32 = m32;
		_33 = m33;
	};

	void SetScale(float a, float b)
	{
		SetIdentity();
		_11 = a;
		_22 = b;
	}

	void SetIdentity()
	{
		_11 = 1.0f;
		_12 = 0.0f;
		_13 = 0.0f;
		_21 = 0.0f;
		_22 = 1.0f;
		_23 = 0.0f;
		_31 = 0.0f;
		_32 = 0.0f;
		_33 = 1.0f;
	};

	void SetRotation(float degree)
	{
		float rad = Deg2Rad(degree);
		_11 = cosf(rad);
		_12 = -sinf(rad);
		_21 = sinf(rad);
		_22 = cosf(rad);
	}

	void SetTransfrom(float tx, float ty)
	{
		_11 = 1.0f;
		_12 = 0.0f;
		_13 = tx;
		_21 = 0.0f;
		_22 = 1.0f;
		_23 = ty;
		_31 = 0.0f;
		_32 = 0.0f;
		_33 = 1.0f;
	}

	Matrix3 operator *(const Matrix2 Other) const;
};