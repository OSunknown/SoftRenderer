#pragma once
#include "Sprite.h"
class SpriteRenderer
{
public:
	Sprite sprite;
	int sortingLayer = 0;
public:
	void SetSortingLayer(int i)
	{
		sortingLayer = i;
	}
public:
	SpriteRenderer();
	~SpriteRenderer();
};

