#pragma once
#include "stdafx.h"
#include "Triangle.h"
#include  "Texture.h"
class Sprite
{
public:
	Vector2 Vertice[4];
	Vector2 uv[4];
	unsigned int Indices[6]; //unity ���� Triangles ��� ��.
	Texture texture;
public:
	static Sprite Create(Texture itexture) //���� ������ texture�� ������ �ɵ� center ����� �ٲٴ� ����� �𸣴�
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
		
		//Vertice[0] = Vertex(Vector3(-halfWidth + position.X, -halfHeight + position.Y, 0), RGB(255, 0, 0), Vector2(0.125f, 0.25f)); //���� �Ʒ�
		//Vertice[1] = Vertex(Vector3(halfWidth + position.X, halfHeight + position.Y, 0), RGB(0, 255, 0),   Vector2(0.25f, 0.125f)); //������ ��
		//Vertice[2] = Vertex(Vector3(-halfWidth + position.X, halfHeight + position.Y, 0), RGB(0, 0, 255),  Vector2(0.125, 0.125f)); //���� ��
		//Vertice[3] = Vertex(Vector3(halfWidth + position.X, -halfHeight + position.Y, 0), RGB(255, 255, 0),Vector2(0.25f, 0.25f)); //������ �Ʒ�
		
		Vertice[0] = Vector2(-halfWidth , -halfHeight); //���� �Ʒ�
		Vertice[1] = Vector2(halfWidth   , halfHeight) ; //������ ��
		Vertice[2] = Vector2(-halfWidth , halfHeight ); //���� ��
		Vertice[3] = Vector2(halfWidth , -halfHeight ); //������ �Ʒ�

		uv[0] = Vector2(0, 0); //���� �Ʒ�
		uv[1] = Vector2(1, 1); //������ ��
		uv[2] = Vector2(0, 1); //���� ��
		uv[3] = Vector2(1, 0); //������ �Ʒ�

		Indices[0] = 0;
		Indices[1] = 1;
		Indices[2] = 2;
		Indices[3] = 0;
		Indices[4] = 1;
		Indices[5] = 3;
	}
	void uvChange(Vector2 LeftButtom, Vector2 RightTop, Vector2 LeftTop, Vector2 RightButtom )
	{
		uv[0] = LeftButtom; //���� �Ʒ�
		uv[1] = RightTop; //������ ��
		uv[2] = LeftTop;//���� ��
		uv[3] = RightButtom; //������ �Ʒ�
	}
};

