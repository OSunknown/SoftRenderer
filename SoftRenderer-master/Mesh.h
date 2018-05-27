#pragma once
#include "stdafx.h"
#include "Vertex.h"
struct Mesh
{
public:
	Vertex* Vertices;
	int* Indices; //unity 에선 Triangles 라는 듯.
	size_t VSize; //Vertex size
	size_t ISize; //IndexSize
public:
	Mesh() : Vertices(NULL), Indices(NULL), ISize(0), VSize(0) { };
	~Mesh() {
		if (NULL != Vertices)
		{
			delete[] Vertices;
			Vertices = NULL;
		}
		if (NULL != Indices)
		{
			delete[] Indices;
			Indices = NULL;
		}
	}
public:
	bool IsInitialized() { return ((NULL != Vertices) && (NULL != Indices) && (ISize % 3 == 0)); }
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

	Vertex GetVertex(int index)
	{
		return Vertices[index];
	}
};