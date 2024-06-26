#include "IParticle.h"
#include "ParticleManager.h"
#include "ModelDataManager.h"
#include "TextureManager.h"
#include "Camera.h"

const ModelData* IParticle::plane_ = nullptr;

void IParticle::StaticInitialize()
{
	plane_ = ModelDataManager::GetInstance()->LoadObj("Plane");
}

void IParticle::Initialize()
{
}

void IParticle::Update(float deltaTime, Camera* camera)
{
#ifdef _DEBUG
	ApplyGlobalVariable();
#endif // _DEBUG


	deltaTime = deltaTime;
	camera->transform_ = camera->transform_;
}

void IParticle::Draw(Camera* camera)
{
	camera->transform_ = camera->transform_;
}

void IParticle::CreateParticle(const std::string& particleName, const std::string& textureName, bool isStageEditor, BlendMode blendMode)
{
	drawData_ = GPUParticleMeshTexData{ plane_,textureManager_->LoadTexture(textureName),blendMode };
	if (isStageEditor) {
		stageEditor_ = std::make_unique<StageEditor>("パーティクルの設定", particleName);
	}
	else {
		globalVariable_ = std::make_unique<GlobalVariableUser>("Particle", particleName);
	}
	SetGlobalVariable();
}

void IParticle::CreateParticle(const std::string& particleName, const std::string& modelName, const std::string& textureName, bool isStageEditor, BlendMode blendMode)
{
	if (textureName == "_") {
		const ModelData* modelData = modelDataManager_->LoadObj(modelName);
		drawData_ = GPUParticleMeshTexData{ modelData, modelData->texture,blendMode };
	}
	else {
		drawData_ = GPUParticleMeshTexData{ modelDataManager_->LoadObj(modelName),textureManager_->LoadTexture(textureName),blendMode };
	}
	if (isStageEditor) {
		stageEditor_ = std::make_unique<StageEditor>("パーティクルの設定", particleName);
	}
	else {
		globalVariable_ = std::make_unique<GlobalVariableUser>("Particle", particleName);
	}
	SetGlobalVariable();
}

//void IParticle::SetGlobalVariable()
//{
//	if (globalVariable_) {
//
//	}
//	if (stageEditor_) {
//
//	}
//
//	ApplyGlobalVariable();
//}
//
//void IParticle::ApplyGlobalVariable()
//{
//	if (globalVariable_) {
//
//	}
//	if (stageEditor_) {
//
//	}
//}
