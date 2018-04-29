#pragma once

#include "stdafx.h"
#include "Vector.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Triangle.h"
#include "Texture.h"
#include "Mesh.h"

void InitFrame(void);
void UpdateFrame(void);
bool IsInRange(int x, int y);
void PutPxel(IntPoint pt);
void DrowCall(Mesh* MeshToDrow);

V2F_CUSTOM VertexShader(APPDATA_CUSTOM in);
ULONG FragmentShader(V2F_CUSTOM in);