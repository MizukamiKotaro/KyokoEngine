#pragma once
#include "Matrix4x4.h"
#include "Vector4.h"
#include "Vector3.h"

struct GPUParticleData {
	Vector3 translate;
	Vector3 scale;
	Vector3 rotate;
	float lifeTime;
	Vector3 velocity;
	float currentTime;
	Vector4 color;
};