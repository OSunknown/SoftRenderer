#pragma once
#include "stdafx.h"
#include "Triangle.h"
#include  "Texture.h"
class Sprite
{
public:
	Vector2 Vertice[4];
	Vector2 uv[4];
	unsigned int Indices[6]; //unity 에선 Triangles 라는 듯.
	Texture texture;
public:
	static Sprite Create(Texture itexture) //지금 당장은 texture만 있으면 될듯 center 라든지 바꾸는 방법을 모르니
	{
		Sprite result;
		result.texture = itexture;
		result.spriteInit();
		return result;
	}
public:
	Sprite() {};
	~Sprite() {};
public:
	void spriteInit()
	{
		spriteInit(texture.width, texture.height);
	}
	void spriteInit(int width, int height)
	{
		float halfWidth = width * 0.5f;
		float halfHeight = height * 0.5f;
		
		//Vertice[0] = Vertex(Vector3(-halfWidth + position.X, -halfHeight + position.Y, 0), RGB(255, 0, 0), Vector2(0.125f, 0.25f)); //왼쪽 아래
		//Vertice[1] = Vertex(Vector3(halfWidth + position.X, halfHeight + position.Y, 0), RGB(0, 255, 0),   Vector2(0.25f, 0.125f)); //오른쪽 위
		//Vertice[2] = Vertex(Vector3(-halfWidth + position.X, halfHeight + position.Y, 0), RGB(0, 0, 255),  Vector2(0.125, 0.125f)); //왼쪽 위
		//Vertice[3] = Vertex(Vector3(halfWidth + position.X, -halfHeight + position.Y, 0), RGB(255, 255, 0),Vector2(0.25f, 0.25f)); //오른쪽 아래
		
		Vertice[0] = Vector2(-halfWidth , -halfHeight); //왼쪽 아래
		Vertice[1] = Vector2(halfWidth   , halfHeight) ; //오른쪽 위
		Vertice[2] = Vector2(-halfWidth , halfHeight ); //왼쪽 위
		Vertice[3] = Vector2(halfWidth , -halfHeight ); //오른쪽 아래

		uv[0] = Vector2(0, 0); //왼쪽 아래
		uv[1] = Vector2(1, 1); //오른쪽 위
		uv[2] = Vector2(0, 1); //왼쪽 위
		uv[3] = Vector2(1, 0); //오른쪽 아래

		Indices[0] = 0;
		Indices[1] = 1;
		Indices[2] = 2;
		Indices[3] = 0;
		Indices[4] = 1;
		Indices[5] = 3;
	}
	void uvChange(Vector2 LeftButtom, Vector2 RightTop, Vector2 LeftTop, Vector2 RightButtom )
	{
		uv[0] = LeftButtom; //왼쪽 아래
		uv[1] = RightTop; //오른쪽 위
		uv[2] = LeftTop;//왼쪽 위
		uv[3] = RightButtom; //오른쪽 아래
	}
};

