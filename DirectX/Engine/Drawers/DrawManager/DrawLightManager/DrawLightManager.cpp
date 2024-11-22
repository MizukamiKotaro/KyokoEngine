#include "DrawLightManager.h"
#include "Camera.h"
#include "ModelDataManager.h"
#include "GraphicsPipelineSystem/GraphicsPiplineManager/GraphicsPiplineManager.h"
#include "ModelData/ModelData.h"
#include "GraphicsPipelineSystem/PipelineTypeConfig.h"
#include "SpotLight/SpotLight.h"
#include "PointLight/PointLight.h"
#include "calc.h"

Matrix4x4 scaleMat;
Matrix4x4 scaleInverseMat;

DrawLightManager::DrawLightManager()
{
	drawNo_ = 0;
	scaleMat = Matrix4x4::MakeScaleMatrix({ 1000.0f,1000.0f,1000.0f });
	scaleInverseMat = Matrix4x4::Inverse(scaleMat);
	modelData_ = ModelDataManager::GetInstance()->LoadObj("plane");
	for (int32_t i = 0; i < 50; i++) {
		transformations_.push_back(std::make_unique<Transformation>());
	}
}

void DrawLightManager::Draw(const PointLight& light, const Camera& camera, BlendMode blendMode)
{
	// ビルボード行列
	Matrix4x4 billboardMat{};
	billboardMat = camera.transform_.worldMat_;
	billboardMat.m[3][0] = 0.0f;
	billboardMat.m[3][1] = 0.0f;
	billboardMat.m[3][2] = 0.0f;

	// 変換行列
	Matrix4x4 translateMat = Matrix4x4::MakeTranslateMatrix(light.light_->position + Vector3{ 0.0f,0.0f,0.1f } * billboardMat);
	if (transformations_.size() == drawNo_) {
		transformations_.push_back(std::make_unique<Transformation>());
	}
	transformations_[drawNo_]->transformationData->World = scaleMat * billboardMat * translateMat;
	transformations_[drawNo_]->transformationData->WVP = transformations_[drawNo_]->transformationData->World * camera.GetViewProjection();
	transformations_[drawNo_]->transformationData->WorldInverse = scaleInverseMat * billboardMat * translateMat;

	// コマンド
	PipelineType piplineType = PipelineType::SPOT_LIGHT;
	psoManager_->PreDraw(piplineType);
	psoManager_->SetBlendMode(piplineType, blendMode);
	commandList_->IASetVertexBuffers(0, 1, &modelData_->mesh.vertexBufferView_);
	commandList_->IASetIndexBuffer(&modelData_->mesh.indexBufferView_);
	commandList_->SetGraphicsRootConstantBufferView(1, transformations_[drawNo_]->transformationResource->GetGPUVirtualAddress());
	commandList_->SetGraphicsRootConstantBufferView(2, camera.GetGPUVirtualAddress());
	commandList_->SetGraphicsRootConstantBufferView(0, light.GetGPUVirtualAddress());
	commandList_->DrawIndexedInstanced(UINT(modelData_->mesh.indices.size()), 1, 0, 0, 0);

	drawNo_++;
}

void DrawLightManager::Draw(const SpotLight& light, const Camera& camera, BlendMode blendMode)
{
	// ビルボード行列
	Matrix4x4 billboardMat{};
	billboardMat = camera.transform_.worldMat_;
	billboardMat.m[3][0] = 0.0f;
	billboardMat.m[3][1] = 0.0f;
	billboardMat.m[3][2] = 0.0f;

	Vector3 project = Calc::Project(camera.transform_.worldPos_ - light.light_->position, light.light_->direction);
	Vector3 rotate = camera.transform_.worldPos_ - (light.light_->position + project);
	rotate = rotate.Normalize();
	if (rotate.z != -1.0f) {
		billboardMat = billboardMat * Matrix4x4::DirectionToDirection(Vector3{ 0.0f,0.0f,-1.0f } * Matrix4x4::MakeRotateXYZMatrix(camera.transform_.rotate_), rotate);
	}

	// 変換行列
	Matrix4x4 translateMat = Matrix4x4::MakeTranslateMatrix(light.light_->position + Vector3{ 0.0f,0.0f,0.1f } * billboardMat);
	if (transformations_.size() == drawNo_) {
		transformations_.push_back(std::make_unique<Transformation>());
	}
	transformations_[drawNo_]->transformationData->World = scaleMat * billboardMat * translateMat;
	transformations_[drawNo_]->transformationData->WVP = transformations_[drawNo_]->transformationData->World * camera.GetViewProjection();
	transformations_[drawNo_]->transformationData->WorldInverse = scaleInverseMat * billboardMat * translateMat;

	// コマンド
	PipelineType piplineType = PipelineType::SPOT_LIGHT;
	psoManager_->PreDraw(piplineType);
	psoManager_->SetBlendMode(piplineType, blendMode);
	commandList_->IASetVertexBuffers(0, 1, &modelData_->mesh.vertexBufferView_);
	commandList_->IASetIndexBuffer(&modelData_->mesh.indexBufferView_);
	commandList_->SetGraphicsRootConstantBufferView(1, transformations_[drawNo_]->transformationResource->GetGPUVirtualAddress());
	commandList_->SetGraphicsRootConstantBufferView(2, camera.GetGPUVirtualAddress());
	commandList_->SetGraphicsRootConstantBufferView(0, light.GetGPUVirtualAddress());
	commandList_->DrawIndexedInstanced(UINT(modelData_->mesh.indices.size()), 1, 0, 0, 0);

	psoManager_->PreDraw(PipelineType::SPOT_LIGHT_DEPTH);
	psoManager_->SetBlendMode(PipelineType::SPOT_LIGHT_DEPTH, BlendMode::kBlendModeAdd);
	commandList_->IASetVertexBuffers(0, 1, &modelData_->mesh.vertexBufferView_);
	commandList_->IASetIndexBuffer(&modelData_->mesh.indexBufferView_);
	commandList_->SetGraphicsRootConstantBufferView(1, transformations_[drawNo_]->transformationResource->GetGPUVirtualAddress());
	commandList_->SetGraphicsRootConstantBufferView(2, camera.GetGPUVirtualAddress());
	commandList_->SetGraphicsRootConstantBufferView(0, light.GetGPUVirtualAddress());
	commandList_->DrawIndexedInstanced(UINT(modelData_->mesh.indices.size()), 1, 0, 0, 0);

	drawNo_++;
}
