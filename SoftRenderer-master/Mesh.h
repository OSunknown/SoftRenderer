#pragma once
#include "stdafx.h"
#include "Triangle.h"
#include "Vertex.h"
struct Mesh
{
public:
	Vertex* Vertices;
	int* Indices;
	size_t VSize; //Vertex size
	size_t ISize; //IndexSize
public:
	Mesh() : Vertices(NULL), Indices(NULL), ISize(0), VSize(0) { }
	~Mesh() {
		
		if (NULL != Vertices)
		{
			Vertices = NULL;
		}

		if (NULL != Indices)
		{
			Indices = NULL;
		}
	}
public:
	void SetVertices(Vertex* vertices, size_t count)
	{
		Vertices = vertices;
		VSize = count;
	}

	void SetIndices(int* indices, size_t count)
	{
		Indices = indices;
		ISize = count;
	}
};