#include "DrawModelManager.h"
#include "Camera.h"
#include "GraphicsPipelineSystem/GraphicsPiplineManager/GraphicsPiplineManager.h"
#include "ModelData/ModelData.h"
#include "GraphicsPipelineSystem/PipelineTypeConfig.h"
#include "Model.h"
#include "SkinningModel/SkinningModel.h"
#include "RigidAnimationModel/RigidAnimationModel.h"
#include "Texture/Texture.h"
#include "TextureManager.h"
#include "MMD/PMDModel/PMDModel.h"
#include "Base/DescriptorHeapManager/DescriptorHeapManager.h"
#include "Base/DescriptorHeapManager/DescriptorHeap/DescriptorHeap.h"

const Texture* texCube = nullptr;

DrawModelManager::DrawModelManager()
{
	texCube = TextureManager::GetInstance()->LoadTexture("rostock_laage_airport_4k.dds");
	drawNo_ = 0;
	for (int32_t i = 0; i < 50; i++) {
		transformations_.push_back(std::make_unique<Transformation>());
	}
}

void DrawModelManager::Draw(const Model& model, const Camera& camera, BlendMode blendMode)
{
	if (transformations_.size() == drawNo_) {
		transformations_.push_back(std::make_unique<Transformation>());
	}

	transformations_[drawNo_]->transformationData->World = model.transform_.worldMat_;
	transformations_[drawNo_]->transformationData->WVP = model.transform_.worldMat_ * camera.GetViewProjection();
	transformations_[drawNo_]->transformationData->WorldInverse = Matrix4x4::Inverse(Matrix4x4::MakeScaleMatrix(model.transform_.scale_)) *
		Matrix4x4::MakeRotateXYZMatrix(model.transform_.rotate_) * Matrix4x4::MakeTranslateMatrix(model.transform_.translate_);

	Draw(model, camera, blendMode, model.GetModelData().mesh.vertexBufferView_);
}

void DrawModelManager::Draw(const RigidAnimationModel& model, const Camera& camera, BlendMode blendMode)
{
	if (transformations_.size() == drawNo_) {
		transformations_.push_back(std::make_unique<Transformation>());
	}
	const QuaternionTransform& animTransform = model.GetAnimTransform();

	transformations_[drawNo_]->transformationData->World = animTransform.matrix_ * model.transform_.worldMat_;
	transformations_[drawNo_]->transformationData->WVP = animTransform.matrix_ * model.transform_.worldMat_ * camera.GetViewProjection();
	transformations_[drawNo_]->transformationData->WorldInverse = Matrix4x4::Inverse(Matrix4x4::MakeScaleMatrix(animTransform.scale_) * Matrix4x4::MakeScaleMatrix(model.transform_.scale_)) *
		(Matrix4x4::MakeRotateMatrix(animTransform.rotate_) * Matrix4x4::MakeRotateXYZMatrix(model.transform_.rotate_)) * (Matrix4x4::MakeTranslateMatrix(animTransform.translate_) * Matrix4x4::MakeTranslateMatrix(model.transform_.translate_));

	Draw(model, camera, blendMode, model.GetModelData().mesh.vertexBufferView_);
}

void DrawModelManager::Draw(const SkinningModel& model, const Camera& camera, BlendMode blendMode)
{
	if (transformations_.size() == drawNo_) {
		transformations_.push_back(std::make_unique<Transformation>());
	}

	transformations_[drawNo_]->transformationData->World = model.transform_.worldMat_;
	transformations_[drawNo_]->transformationData->WVP = model.transform_.worldMat_ * camera.GetViewProjection();
	transformations_[drawNo_]->transformationData->WorldInverse = Matrix4x4::Inverse(Matrix4x4::MakeScaleMatrix(model.transform_.scale_)) *
		Matrix4x4::MakeRotateXYZMatrix(model.transform_.rotate_) * Matrix4x4::MakeTranslateMatrix(model.transform_.translate_);

	Draw(model, camera, blendMode, model.GetSkinCluter().vertexBufferView);
}

void DrawModelManager::Draw(const PMDModel& model, const Camera& camera, BlendMode blendMode)
{
	if (transformations_.size() == drawNo_) {
		transformations_.push_back(std::make_unique<Transformation>());
	}

	transformations_[drawNo_]->transformationData->World = model.transform_.worldMat_;
	transformations_[drawNo_]->transformationData->WVP = model.transform_.worldMat_ * camera.GetViewProjection();
	transformations_[drawNo_]->transformationData->WorldInverse = Matrix4x4::Inverse(Matrix4x4::MakeScaleMatrix(model.transform_.scale_)) *
		Matrix4x4::MakeRotateXYZMatrix(model.transform_.rotate_) * Matrix4x4::MakeTranslateMatrix(model.transform_.translate_);

	psoManager_->PreDraw(PipelineType::MMD);
	psoManager_->SetBlendMode(PipelineType::MMD, blendMode);
	const ModelDataPMD& modelData = model.GetModelData();

	commandList_->IASetVertexBuffers(0, 1, &model.GetSkinCluter().vertexBufferView);
	commandList_->IASetIndexBuffer(&modelData.mesh.indexBufferView_);
	commandList_->SetGraphicsRootConstantBufferView(0, transformations_[drawNo_]->transformationResource->GetGPUVirtualAddress());
	commandList_->SetGraphicsRootDescriptorTable(1, DescriptorHeapManager::GetInstance()->GetSRVDescriptorHeap()->GetTextureFirstHandle());
	commandList_->SetGraphicsRootConstantBufferView(2, camera.GetGPUVirtualAddress());
	commandList_->DrawIndexedInstanced(UINT(modelData.mesh.indices.size()), 1, 0, 0, 0);
	drawNo_++;
}

void DrawModelManager::Finalize()
{
	transformations_.clear();
}

void DrawModelManager::Draw(const BaseModel& model, const Camera& camera, BlendMode blendMode, D3D12_VERTEX_BUFFER_VIEW vertexBufferView)
{
	psoManager_->PreDraw(PipelineType::MODEL);
	psoManager_->SetBlendMode(PipelineType::MODEL, blendMode);
	const ModelData& modelData = model.GetModelData();
	const Light& light = model.GetLight();
	commandList_->IASetVertexBuffers(0, 1, &vertexBufferView);
	commandList_->IASetIndexBuffer(&modelData.mesh.indexBufferView_);
	commandList_->SetGraphicsRootConstantBufferView(0, model.GetMaterialData().GetGPUVirtualAddress());
	commandList_->SetGraphicsRootConstantBufferView(1, transformations_[drawNo_]->transformationResource->GetGPUVirtualAddress());
	commandList_->SetGraphicsRootDescriptorTable(2, model.GetTextureData());
	commandList_->SetGraphicsRootConstantBufferView(3, light.GetDirectionalLightGPUVirtualAddress());
	commandList_->SetGraphicsRootConstantBufferView(4, camera.GetGPUVirtualAddress());
	commandList_->SetGraphicsRootConstantBufferView(5, light.GetPointLightGPUVirtualAddress());
	commandList_->SetGraphicsRootConstantBufferView(6, light.GetSpotLightGPUVirtualAddress());
	commandList_->SetGraphicsRootDescriptorTable(7, texCube->handles_->gpuHandle);
	commandList_->DrawIndexedInstanced(UINT(modelData.mesh.indices.size()), 1, 0, 0, 0);
	drawNo_++;
}
