#include "GPUParticle.h"
#include "ParticleManager.h"
#include "ModelDataManager.h"
#include "TextureManager.h"
#include "Camera.h"

GPUParticle::GPUParticle(const std::string& particleName, const std::string& textureName, bool isStageEditor, BlendMode blendMode)
{
	CreateParticle(particleName, textureName, isStageEditor, blendMode);
}

GPUParticle::GPUParticle(const std::string& particleName, const std::string& modelName, const std::string& textureName, bool isStageEditor, BlendMode blendMode)
{
	CreateParticle(particleName, modelName, textureName, isStageEditor, blendMode);
}

void GPUParticle::Initialize()
{
}

void GPUParticle::Update(float deltaTime, Camera* camera)
{
#ifdef _DEBUG
	ApplyGlobalVariable();
#endif // _DEBUG


	deltaTime = deltaTime;
	camera->transform_ = camera->transform_;
}

void GPUParticle::Draw(Camera* camera)
{
	camera->transform_ = camera->transform_;
}

void GPUParticle::SetGlobalVariable()
{
	if (globalVariable_) {

	}
	if (stageEditor_) {

	}

	ApplyGlobalVariable();
}

void GPUParticle::ApplyGlobalVariable()
{
	if (globalVariable_) {

	}
	if (stageEditor_) {

	}
}
