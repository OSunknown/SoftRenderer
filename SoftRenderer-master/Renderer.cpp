
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"
#include "Vector.h"



bool IsInRange(int x, int y);
void PutPixel(int x, int y);

bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}

void PutPixel(int x, int y)
{
	if (!IsInRange(x, y)) return;

	ULONG* dest = (ULONG*)g_pBits;
	DWORD offset = g_nClientWidth * g_nClientHeight / 2 + g_nClientWidth / 2 + x + g_nClientWidth * -y;
	*(dest + offset) = g_CurrentColor;
}

void DrawC(int a, int b, int r)
{
	Vector2 Center(0.0f, 0.0f);

	for (int i = -r; i < r; i++)
	{
		for (int j = -r; j < r; j++)
		{
			Vector2 CurrentPos(i, j);
			if (Vector2::DistSquared(Center, CurrentPos) < (r*r))
			{
				PutPixel(i, j);
			}
		}
	}

}


void DrawLine(Vector3 start, Vector3 dest);

Vector3 Pt1, Pt2;
Vector2 TempPt1, TempPt2;
bool IsMove = true, IsRotation = false, IsScale = false;
static float angle = 0.0f;
float Pt1x = 0, Pt1y = 0;
float Pt2x = 100, Pt2y = 100;
float tx = 1.0f, ty = 1.0f;
float ScaleX = 1.0f, ScaleY = 1.0f;
void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	static Matrix2 Scale;

	if (GetAsyncKeyState('W'))
	{
		IsMove = true;
		IsRotation = false;
		IsScale = false;
		angle = 0.0f;
	}

	if (GetAsyncKeyState('E'))
	{
		IsMove = false;
		IsRotation = true;
		IsScale = false;
	}

	if (GetAsyncKeyState('R'))
	{
		IsMove = false;
		IsRotation = false;
		IsScale = true;
	}

	Matrix3 Affine;
	Matrix2 Rotation;
	
	
	if (Pt1.ZeroCheck() && Pt2.ZeroCheck())
	{
		Pt1.SetPoint(Pt1x, Pt1y);
		Pt2.SetPoint(Pt2x, Pt2y);
		TempPt1.X = Pt1x;
		TempPt1.Y = Pt1y;
		TempPt2.X = Pt2x;
		TempPt2.Y = Pt2y;
		Rotation.SetIdentity();
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (IsMove)
		{
			Affine.SetTransfrom(-tx, 0.0f);
			Pt1 = Pt1 * Affine;
			Pt2 = Pt2 * Affine;
		}

		if (IsRotation)
		{
			angle = 1.0f;
		}

		if (IsScale)
		{
			ScaleX = -0.0001f;
			Scale.SetScale(ScaleX, ScaleY);
			TempPt1 = TempPt1 * Scale;
			TempPt2 = TempPt2 * Scale;
			Pt1.SetPoint(TempPt1.X, TempPt1.Y);
			Pt2.SetPoint(TempPt2.X, TempPt2.Y);
		}
		
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (IsMove)
		{
			Affine.SetTransfrom(tx, 0.0f);
			Pt1 = Pt1 * Affine;
			Pt2 = Pt2 * Affine;
		}

		if (IsRotation)
		{
			angle = -1.0f;
		}

		if (IsScale)
		{
			ScaleX += 0.0001f;
			Scale.SetScale(ScaleX, ScaleY);
			TempPt1 = TempPt1 * Scale;
			TempPt2 = TempPt2 * Scale;
			Pt1.SetPoint(TempPt1.X, TempPt1.Y);
			Pt2.SetPoint(TempPt2.X, TempPt2.Y);
		}
	}
	if (GetAsyncKeyState(VK_UP))
	{
		if (IsMove)
		{
			Affine.SetTransfrom(0.0f, ty);
			Pt1 = Pt1 * Affine;
			Pt2 = Pt2 * Affine;
		}

		if (IsScale)
		{
			ScaleY += 0.0001f;
			Scale.SetScale(ScaleX, ScaleY);
			TempPt1 = TempPt1 * Scale;
			TempPt2 = TempPt2 * Scale;
			Pt1.SetPoint(TempPt1.X, TempPt1.Y);
			Pt2.SetPoint(TempPt2.X, TempPt2.Y);
		}
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		if (IsMove)
		{
			Affine.SetTransfrom(0.0f, -ty);
			Pt1 = Pt1 * Affine;
			Pt2 = Pt2 * Affine;
		}

		if (IsScale)
		{
			ScaleY += -0.0001f;
			Scale.SetScale(ScaleX, ScaleY);
			TempPt1 = TempPt1 * Scale;
			TempPt2 = TempPt2 * Scale;
			Pt1.SetPoint(TempPt1.X, TempPt1.Y);
			Pt2.SetPoint(TempPt2.X, TempPt2.Y);
		}
	}
	
	if (IsRotation)
	{
		Rotation.SetRotation(angle);
		TempPt1 = TempPt1 * Rotation;
		TempPt2 = TempPt2 * Rotation;
		Pt1.SetPoint(TempPt1.X, TempPt1.Y);
		Pt2.SetPoint(TempPt2.X, TempPt2.Y);
	}
	
	SetColor(255, 0, 0);
	DrawLine(Pt1, Pt2);

	// Draw
	//SetColor(255, 0, 0);
	//PutPixel(0, 0);
	//DrawC(50,100, 100);

	
	/*
	static float angle = 0.0f;
	angle += 0.1f;

	Vector2 Center(0.0f, 0.0f);
	float radius = 100.0f;
	int nradius = (int)radius;

	Matrix2 Scale;
	Scale.SetScale(1.5f,0.1f);

	Matrix2 Rotation;
	Rotation.SetRotation(angle);

	for (int i = -nradius + Center.X; i < nradius+ Center.X; i++)
	{
		for (int j = -nradius+ Center.Y; j < nradius + Center.Y; j++)
		{
			Vector2 CurrentPos(i, j);
			if (Vector2::DistSquared(Center, CurrentPos) < radius*radius)
			{
				Vector2 newPos = CurrentPos *Scale;
				newPos = newPos * Rotation;
				PutPixel(newPos.X+ Center.X, newPos.Y+ Center.Y);
			}
		}
	}*/


	// Buffer Swap 
	BufferSwap();
}

void DrawLine(Vector3 start, Vector3 dest)
{
	float XLength;
	float YLength;
	float Xpoint;
	float Ypoint;

	if (start.X == dest.X)
	{
		XLength = 1;
		Xpoint = 0;
	}
	else
	{
		XLength = (start.X - dest.X) >= 0.0f ? (start.X - dest.X) : (start.X - dest.X)*-1;
		if ((start.X > dest.X))
		{
			Xpoint = -XLength/100.0f;
		}
		else
		{
			Xpoint = XLength/100.0f;
		}
	}

	if (start.Y == dest.Y)
	{
		YLength = 1;
		Ypoint = 0;
	}
	else
	{
		YLength = (start.Y - dest.Y) >= 0.0f ? (start.Y - dest.Y) : (start.Y - dest.Y)*-1;
		if ((start.Y > dest.Y))
		{
			Ypoint = -YLength/100.0f;
		}
		else
		{
			Ypoint = YLength/100.0f;
		}
	}
	Vector3 StartPoint;
	StartPoint.X = (start.X);
	StartPoint.Y = (start.Y);
	float tempX = 0;
	float tempY = 0;
	while (true)
	{

		if (StartPoint.X != dest.X)
		{
			/*if (XLength < YLength)
			{
			if (XCount == 0)
			{
			XCount = YLength / XLength;
			StartPoint.X += Xpoint;
			tempX++;
			}
			else
			{
			XCount--;
			}
			}
			else
			{
			StartPoint.X += Xpoint;
			tempX++;
			}*/
			StartPoint.X += Xpoint;
			tempX += Xpoint;
			
		}
		if (StartPoint.Y != dest.Y)
		{
			/*if (XLength > YLength)
			{
			if (YCount == 0)
			{
			YCount = XLength / YLength;
			StartPoint.Y += Ypoint;
			tempY++;
			}
			else
			{
			YCount--;
			}
			}
			else
			{
			StartPoint.Y += Ypoint;
			tempY++;
			}*/
			StartPoint.Y += Ypoint;
			tempY += Ypoint;
		}

		PutPixel(StartPoint.X, StartPoint.Y);
		if(IsRotation)
			if(fabs(dest.X - tempX) < 1.0f && fabs(dest.Y - tempY) < 1.0f)
			{
				break;
			}
		if (IsMove || IsScale)
		{
			if (fabs(StartPoint.X) >= fabs(dest.X) && fabs(StartPoint.Y) >= fabs(dest.Y))
			{
				break;
			}
		}
	}
	
}