#include "RigidAnimationModel.h"

#include <cassert>
#include "TextureManager/TextureManager.h"
#include "Engine/Base/DirectXBase/DirectXBase.h"
#include "ModelDataManager.h"
#include "Camera.h"
#include "DescriptorHeapManager/DescriptorHandles/DescriptorHandles.h"
#include "calc.h"
#include "DescriptorHeapManager/DescriptorHeapManager.h"
#include "DescriptorHeapManager/DescriptorHeap/DescriptorHeap.h"

RigidAnimationModel::RigidAnimationModel(const std::string& fileName)
{
	LoadGLTF(fileName);
	CreateResources();
	InitVariables();
}

RigidAnimationModel::RigidAnimationModel(const ModelData* modelData, const std::string& fileName)
{
	modelData_ = modelData;
	texture_ = modelData_->texture;
	srvGPUDescriptorHandle_ = texture_->handles_->gpuHandle;
	LoadAnimation(fileName);
	CreateResources();
	InitVariables();
}

void RigidAnimationModel::Update(const float& time)
{
	BaseModel::Update();
	AnimationUpdate(time);
}

void RigidAnimationModel::Draw(const Camera& camera, BlendMode blendMode)
{

	materialData_->color = color_;
	materialData_->uvTransform = uvMatrix_;

	NodeAnimation& rootNodeAnimation = animation_->nodeAnimations[modelData_->rootNode.name];
	Vector3 translate = CalculateValue(rootNodeAnimation.translate, animationTime_);
	Quaternion rotate = CalculateValue(rootNodeAnimation.rotate, animationTime_);
	Vector3 scale = CalculateValue(rootNodeAnimation.scale, animationTime_);
	Matrix4x4 localMatrix = Matrix4x4::MakeAffinMatrix(scale, rotate, translate);

	transformationData_->World = localMatrix * transform_.worldMat_;
	transformationData_->WVP = localMatrix * transform_.worldMat_ * camera.GetViewProjection();
	transformationData_->WorldInverse = Matrix4x4::Inverse(Matrix4x4::MakeScaleMatrix(transform_.scale_) * Matrix4x4::MakeScaleMatrix(scale)) *
		Matrix4x4::MakeRotateXYZMatrix(transform_.rotate_) * Matrix4x4::MakeRotateMatrix(rotate) * Matrix4x4::MakeTranslateMatrix(transform_.translate_) * Matrix4x4::MakeTranslateMatrix(translate);


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

void RigidAnimationModel::AnimationUpdate(const float& time)
{
	if (animation_) {
		if (time < 0) {
			animationTime_ += time;
			if (animationTime_ < 0) {
				animationTime_ = animation_->duration + animationTime_;
			}
		}
		else {
			animationTime_ += time;
			animationTime_ = std::fmod(animationTime_, animation_->duration);
		}
	}
}

void RigidAnimationModel::LoadGLTF(const std::string& fileName)
{
	modelData_ = modelDataManager_->LoadGLTF(fileName);

	texture_ = modelData_->texture;

	srvGPUDescriptorHandle_ = texture_->handles_->gpuHandle;

	LoadAnimation(fileName);
}

void RigidAnimationModel::LoadAnimation(const std::string& fileName)
{
	animationTime_ = 0.0f;
	animation_ = std::make_unique<Animation>(modelDataManager_->LoadAnimation(fileName));
}

const Matrix4x4 RigidAnimationModel::GetRotateMatrix()
{
	NodeAnimation& rootNodeAnimation = animation_->nodeAnimations[modelData_->rootNode.name];
	Quaternion rotate = CalculateValue(rootNodeAnimation.rotate, animationTime_);
	return Matrix4x4::MakeRotateXYZMatrix(transform_.rotate_) * Matrix4x4::MakeRotateMatrix(rotate);
}

Vector3 RigidAnimationModel::CalculateValue(const AnimationCurve<Vector3>& keyframes, const float& time)
{
	assert(!keyframes.keyframes.empty());
	if (keyframes.keyframes.size() == 1 || time <= keyframes.keyframes[0].time) {
		return keyframes.keyframes[0].value;
	}
	for (size_t index = 0; index < keyframes.keyframes.size() - 1; index++) {
		size_t nextIndex = index + 1;
		if (keyframes.keyframes[index].time <= time && time <= keyframes.keyframes[nextIndex].time) {
			float t = (time - keyframes.keyframes[index].time) / (keyframes.keyframes[nextIndex].time - keyframes.keyframes[index].time);
			return Calc::Lerp(keyframes.keyframes[index].value, keyframes.keyframes[nextIndex].value, t);
		}
	}

	return (*keyframes.keyframes.rbegin()).value;
}

Quaternion RigidAnimationModel::CalculateValue(const AnimationCurve<Quaternion>& keyframes, const float& time) {
	assert(!keyframes.keyframes.empty());
	if (keyframes.keyframes.size() == 1 || time <= keyframes.keyframes[0].time) {
		return keyframes.keyframes[0].value;
	}
	for (size_t index = 0; index < keyframes.keyframes.size() - 1; index++) {
		size_t nextIndex = index + 1;
		if (keyframes.keyframes[index].time <= time && time <= keyframes.keyframes[nextIndex].time) {
			float t = (time - keyframes.keyframes[index].time) / (keyframes.keyframes[nextIndex].time - keyframes.keyframes[index].time);
			return Quaternion::Slerp(keyframes.keyframes[index].value, keyframes.keyframes[nextIndex].value, t);
		}
	}

	return (*keyframes.keyframes.rbegin()).value;
}

int32_t RigidAnimationModel::Createjoint(const NodeData& node, const std::optional<int32_t>& parent, std::vector<Joint>& joints)
{
	Joint joint;
	joint.name = node.name;
	joint.localMatrix = node.localMatrix;
	joint.skeletonSpaceMatrix = Matrix4x4::MakeIdentity4x4();
	joint.transform = node.transform;
	joint.index = int32_t(joints.size());
	joint.parent = parent;
	joints.push_back(joint);
	for (const NodeData& child : node.children) {
		int32_t childIndex = Createjoint(child, joint.index, joints);
		joints[joint.index].children.push_back(childIndex);
	}
	return 0;
}