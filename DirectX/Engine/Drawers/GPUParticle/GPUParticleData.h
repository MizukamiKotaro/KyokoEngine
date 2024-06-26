#pragma once
#include "Matrix4x4.h"
#include "Vector4.h"
#include "ModelData/ModelData.h"
#include "GraphicsPipelineSystem/BlendModeConfig.h"

class GPUParticleMeshTexData {
public:
	const ModelData* modelData_;
	const Texture* texture_;
	BlendMode blendMode_;
};

class GPUParticleData {
public:
	Vector3 translate;
	Vector3 scale;
	Vector3 rotate;
	float lifeTime;
	Vector3 velocity;
	float currentTime;
	Vector4 color;
};