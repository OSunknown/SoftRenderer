
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
	// x^2 + y^2 = r^2
	/*for (int i = -r ; i < r ; i++)
	{
		for (int j = -r; j < r; j++)
		{
			if((i*i) + (j*j) <= (r*r))
				PutPixel(i+a, j+b);
		}
	}*/

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


void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	// Draw
	SetColor(255, 0, 0);
	//PutPixel(0, 0);
	DrawC(50,100, 100);
	// Buffer Swap 
	BufferSwap();
}

