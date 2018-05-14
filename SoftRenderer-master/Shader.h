#pragma once
#include "Vertex.h"
#include "Vector.h"
#include "Matrix.h"
#include "Texture.h"
struct MatrixBuffer
{
	Matrix3 worldMatrix;
	Matrix3 viewMatrix;
	Matrix3 projectionMatrix;
};

class VertexInputType
{
public:
	Vector3 position; // SV_POSITION;
	Vector2 uv;
	ULONG color;// : COLOR;
public:
	virtual Vector3 GetPosition() = 0;
	virtual ULONG GetColor() = 0;
	virtual Vector2 GetUV() = 0;
};


class VertexInputTypeColor : public VertexInputType
{
public:
	Vector3 position; // SV_POSITION;
	Vector2 uv;
	ULONG color;// : COLOR;
public:
	Vector3 GetPosition()
	{
		return position;
	}
	ULONG GetColor()
	{
		return color;
	}
	Vector2 GetUV()
	{
		return uv;
	}
};

class VertexInputTypeTexture : public VertexInputType
{
public:
	Vector3 position; // SV_POSITION;
	Vector2 uv;
	ULONG color;// : COLOR;
public:
	Vector3 GetPosition()
	{
		return position;
	}
	ULONG GetColor()
	{
		return color;
	}
	Vector2 GetUV()
	{
		return uv;
	}
};

class PixelInputType
{
public:
	Vector3 position; // SV_POSITION;
	Vector2 uv;
	ULONG color;// : COLOR;
};

class Shader
{
public:
	MatrixBuffer matrixBuffer;
	
public:
	Shader() {};
	~Shader() {};
	virtual VertexInputType * vInput(Vertex v) = 0;
	virtual PixelInputType VertexShader(VertexInputType * input) = 0;
	virtual ULONG PixelShader(PixelInputType input) = 0;
};

class colorShader : public Shader
{
public:
	MatrixBuffer matrixBuffer;
public:
	colorShader() {};
	~colorShader() {};
public:
	VertexInputType * vInput(Vertex v)
	{
		VertexInputTypeColor * result = new VertexInputTypeColor();
		result->position = v.position;
		result->color = v.color;
		result->uv = v.uv;
		VertexInputType * convert = result;
		return convert;
	}

	PixelInputType VertexShader(VertexInputType * input)
	{
		PixelInputType output;
		output.position = input->GetPosition();
		return PixelInputType();
	}
	ULONG PixelShader(PixelInputType input)
	{
		return input.color;
	}

};

struct TextureShader : public Shader
{
public:
	MatrixBuffer matrixBuffer;
	Texture * texcoord0;
private:
public:
	TextureShader(Matrix3 world, Matrix3 view, Matrix3 projection) {
		matrixBuffer.worldMatrix = world;
		matrixBuffer.viewMatrix = view;
		matrixBuffer.projectionMatrix = projection;
	};
	~TextureShader() {};
public:
	void SetTexcoord0(Texture * texcoord)
	{
		texcoord0 = texcoord;
	}
	VertexInputType * vInput(Vertex v)
	{
		VertexInputTypeTexture * result = new VertexInputTypeTexture();
		result->position = v.position;
		result->color = v.color;
		result->uv = v.uv;
		VertexInputType * convert = result;
		return convert;
	}

	PixelInputType VertexShader(VertexInputType * input)
	{
		PixelInputType result;
		result.position = input->GetPosition() * matrixBuffer.worldMatrix;
		result.color = input->GetColor();
		result.uv = input->GetUV();
		return result;
	}
	ULONG PixelShader(PixelInputType input)
	{
		if (texcoord0->IsLoaded())
		{
			return texcoord0->TextureSample(input.uv);
		}
		else
		{
			return input.color;
		}

		return RGB32(255, 255, 255);
	}

};