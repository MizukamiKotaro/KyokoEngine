#pragma once

#include "Utils/Math/Vector2.h"
#include "Utils/Math/Vector3.h"
#include "Utils/Math/Vector4.h"

struct VertexData
{
	Vector4 vertexPos;
	Vector2 texcoord;
	Vector3 normal;

	Vector4 diffuseColor;
	int32_t textureNum;
};