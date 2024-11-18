#pragma once

#include "Utils/Math/Vector2.h"
#include "Utils/Math/Vector3.h"
#include "Utils/Math/Vector4.h"
#include <cstdint>

struct VertexDataPMD
{
	Vector4 vertexPos;
	Vector2 texcoord;
	Vector3 normal;

	Vector4 diffuseColor;
	int32_t textureNum;

	Vector3 ambientColor;
	Vector3 specularColor;
	float shinines;
	int32_t sphereTextureNum;
	int32_t toonTextureNum;

};