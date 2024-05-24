#include "Model.h"

#include <cassert>
#include "TextureManager/TextureManager.h"
#include "Engine/Base/DirectXBase/DirectXBase.h"
#include "ModelDataManager.h"
#include "Camera.h"
#include "DescriptorHeapManager/DescriptorHandles/DescriptorHandles.h"
#include "calc.h"
#include "DescriptorHeapManager/DescriptorHeapManager.h"
#include "DescriptorHeapManager/DescriptorHeap/DescriptorHeap.h"

Model::Model(const std::string& fileName)
{
	CreateModel(fileName);
}

Model::Model(const ModelData* modelData)
{
	CreateModel(modelData);
}

void Model::Draw(const Camera& camera, BlendMode blendMode)
{

	materialData_->color = color_;
	materialData_->uvTransform = uvMatrix_;

	transformationData_->World = transform_.worldMat_;
	transformationData_->WVP = transform_.worldMat_ * camera.GetViewProjection();
	transformationData_->WorldInverse = Matrix4x4::Inverse(Matrix4x4::MakeScaleMatrix(transform_.scale_)) *
		Matrix4x4::MakeRotateXYZMatrix(transform_.rotate_) * Matrix4x4::MakeTranslateMatrix(transform_.translate_);

	psoManager_->PreDraw(PipelineType::MODEL);
	psoManager_->SetBlendMode(PipelineType::MODEL, blendMode);

	//Spriteの描画。変更に必要なものだけ変更する
	commandList_->IASetVertexBuffers(0, 1, &modelData_->mesh.vertexBufferView_); // VBVを設定
	commandList_->IASetIndexBuffer(&modelData_->mesh.indexBufferView_);

	//マテリアルCBufferの場所を設定
	commandList_->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());
	//TransformationMatrixCBufferの場所を設定
	commandList_->SetGraphicsRootConstantBufferView(1, transformationResource_->GetGPUVirtualAddress());

	//平行光源CBufferの場所を設定
	commandList_->SetGraphicsRootConstantBufferView(3, light_.GetDirectionalLightGPUVirtualAddress());
	// カメラの設定
	commandList_->SetGraphicsRootConstantBufferView(4, camera.GetGPUVirtualAddress());
	// pointLight の設定
	commandList_->SetGraphicsRootConstantBufferView(5, light_.GetPointLightGPUVirtualAddress());
	// spotLight の設定
	commandList_->SetGraphicsRootConstantBufferView(6, light_.GetSpotLightGPUVirtualAddress());

	commandList_->SetGraphicsRootDescriptorTable(2, srvGPUDescriptorHandle_);
	//描画!!!!（DrawCall/ドローコール）
	//commandList_->DrawInstanced(UINT(modelData_->mesh.verteces.size()), 1, 0, 0);
	commandList_->DrawIndexedInstanced(UINT(modelData_->mesh.indices.size()), 1, 0, 0, 0);
}