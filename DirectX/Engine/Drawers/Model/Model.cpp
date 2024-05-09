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
	modelData_ = modelDataManager_->LoadObj(fileName);

	texture_ = modelData_->texture;

	srvGPUDescriptorHandle_ = texture_->handles_->gpuHandle;

	CreateResources();

	InitVariables();
}

Model::Model(const ModelData* modelData)
{
	modelData_ = modelData;

	texture_ = modelData_->texture;

	srvGPUDescriptorHandle_ = texture_->handles_->gpuHandle;

	CreateResources();

	InitVariables();
}

Model::~Model()
{
	transformationResource_->Release();
	materialResource_->Release();
	if (skinCluter_) {
		skinCluter_->influenceResouce->Release();
		skinCluter_->paletteResouce->Release();
	}
}

void Model::StaticInitialize()
{
	modelDataManager_ = ModelDataManager::GetInstance();
	commandList_ = DirectXBase::GetInstance()->GetCommandList();
	psoManager_ = GraphicsPipelineManager::GetInstance();
}

void Model::Initialize()
{
	
}

void Model::Update()
{
	transform_.UpdateMatrix();

	uvMatrix_ = Matrix4x4::MakeAffinMatrix(uvScale_, uvRotate_, uvPos_);
}

void Model::PreDraw() 
{
	psoManager_->PreDraw(pipelineType_);
}

void Model::Draw(const Camera& camera, BlendMode blendMode)
{

	materialData_->color = color_;
	materialData_->uvTransform = uvMatrix_;

	if (animation_) {

		//NodeAnimation& rootNodeAnimation = animation_->nodeAnimations[modelData_->rootNode.name];
		//Vector3 translate = CalculateValue(rootNodeAnimation.translate, animationTime_);
		//Quaternion rotate = CalculateValue(rootNodeAnimation.rotate, animationTime_);
		//Vector3 scale = CalculateValue(rootNodeAnimation.scale, animationTime_);
		//Matrix4x4 localMatrix = Matrix4x4::MakeAffinMatrix(scale, rotate, translate);

		//transformationData_->World = localMatrix * transform_.worldMat_;
		//transformationData_->WVP = localMatrix * transform_.worldMat_ * camera.GetViewProjection();
		//transformationData_->WorldInverse = Matrix4x4::Inverse(Matrix4x4::MakeScaleMatrix(transform_.scale_) * Matrix4x4::MakeScaleMatrix(scale)) *
		//	Matrix4x4::MakeRotateXYZMatrix(transform_.rotate_) * Matrix4x4::MakeRotateMatrix(rotate) * Matrix4x4::MakeTranslateMatrix(transform_.translate_) * Matrix4x4::MakeTranslateMatrix(translate);
		///*transformationData_->WorldInverse = Matrix4x4::Inverse(Matrix4x4::MakeScaleMatrix(transform_.scale_)) *
		transformationData_->World = transform_.worldMat_;
		transformationData_->WVP = transform_.worldMat_ * camera.GetViewProjection();
		transformationData_->WorldInverse = Matrix4x4::Inverse(Matrix4x4::MakeScaleMatrix(transform_.scale_)) *
			Matrix4x4::MakeRotateXYZMatrix(transform_.rotate_) * Matrix4x4::MakeTranslateMatrix(transform_.translate_);
		//	Matrix4x4::MakeRotateXYZMatrix(transform_.rotate_) * Matrix4x4::MakeTranslateMatrix(transform_.translate_);*/

		psoManager_->PreDraw(PipelineType::SKINNING_MODEL);
		psoManager_->SetBlendMode(PipelineType::SKINNING_MODEL, blendMode);

		D3D12_VERTEX_BUFFER_VIEW vbvs[2] = {
			modelData_->mesh.vertexBufferView_,
			skinCluter_->influenceBufferView
		};

		//Spriteの描画。変更に必要なものだけ変更する
		commandList_->IASetVertexBuffers(0, 2, vbvs); // VBVを設定
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

		commandList_->SetGraphicsRootDescriptorTable(7, skinCluter_->paletteSrvHandle->gpuHandle);
		//描画!!!!（DrawCall/ドローコール）
		//commandList_->DrawInstanced(UINT(modelData_->mesh.verteces.size()), 1, 0, 0);
		commandList_->DrawIndexedInstanced(UINT(modelData_->mesh.indices.size()), 1, 0, 0, 0);
	}
	else {


		transformationData_->World = transform_.worldMat_;
		transformationData_->WVP = transform_.worldMat_ * camera.GetViewProjection();
		transformationData_->WorldInverse = Matrix4x4::Inverse(Matrix4x4::MakeScaleMatrix(transform_.scale_)) *
			Matrix4x4::MakeRotateXYZMatrix(transform_.rotate_) * Matrix4x4::MakeTranslateMatrix(transform_.translate_);

		PreDraw();
		psoManager_->SetBlendMode(pipelineType_, blendMode);

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
}

void Model::AnimationUpdate(float time)
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
		ApplyAnimation();
		UpdateSkeleton();
		UpdateSkinAnimation();
	}
}

void Model::LoadGLTF(const std::string& fileName)
{
	modelData_ = modelDataManager_->LoadSkinAnimationModel(fileName);

	texture_ = modelData_->texture;

	srvGPUDescriptorHandle_ = texture_->handles_->gpuHandle;

	LoadAnimation(fileName);
}

void Model::LoadAnimation(const std::string& fileName)
{
	animationTime_ = 0.0f;
	animation_ = std::make_unique<Animation>(modelDataManager_->LoadAnimation(fileName));
	CreateSkeleton();
	CreateSkinCluster();
}

void Model::SetTexture(const Texture* texture)
{
	texture_ = texture;

	srvGPUDescriptorHandle_ = texture_->handles_->gpuHandle;
}

void Model::SetModelData(const ModelData* modelData)
{
	modelData_ = modelData;

	texture_ = modelData_->texture;

	srvGPUDescriptorHandle_ = texture_->handles_->gpuHandle;
}

void Model::SetLight(const ILight* light)
{
	light_.SetLight(light);
}

const Matrix4x4 Model::GetRotateMatrix()
{
	if (animation_) {
		NodeAnimation& rootNodeAnimation = animation_->nodeAnimations[modelData_->rootNode.name];
		Quaternion rotate = CalculateValue(rootNodeAnimation.rotate, animationTime_);
		return Matrix4x4::MakeRotateXYZMatrix(transform_.rotate_) * Matrix4x4::MakeRotateMatrix(rotate);
	}
	return Matrix4x4::MakeRotateXYZMatrix(transform_.rotate_);
}

Vector3 Model::CalculateValue(const AnimationCurve<Vector3>& keyframes, const float& time)
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

Quaternion Model::CalculateValue(const AnimationCurve<Quaternion>& keyframes, const float& time) {
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

void Model::CreateResources()
{
	CreateMaterialResource();

	CreateTransformationResource();
}

void Model::CreateMaterialResource()
{
	materialResource_ = DirectXBase::CreateBufferResource(sizeof(Material));

	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));

	materialData_->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	color_ = { 1.0f, 1.0f, 1.0f, 1.0f };
	materialData_->enableLighting = 3;
	materialData_->uvTransform = Matrix4x4::MakeIdentity4x4();
	materialData_->shininess = 40.0f;
	materialData_->supeqularColor = { 1.0f, 1.0f, 1.0f };
}

void Model::CreateTransformationResource()
{
	//WVP用のリソースを作る。Matrix4x4　1つ分のサイズを用意する
	transformationResource_ = DirectXBase::CreateBufferResource(sizeof(TransformationMatrix));
	transformationData_ = nullptr;
	transformationResource_->Map(0, nullptr, reinterpret_cast<void**>(&transformationData_));
	*transformationData_ = { Matrix4x4::MakeIdentity4x4() ,Matrix4x4::MakeIdentity4x4(), Matrix4x4::Inverse(Matrix4x4::MakeIdentity4x4()) };
}

void Model::InitVariables()
{
	light_.Initialize();

	transform_ = EulerTransform();

	uvScale_ = { 1.0f,1.0f,1.0f };
	uvRotate_ = { 0.0f,0.0f,0.0f };
	uvPos_ = { 0.0f,0.0f,0.0f };

	uvMatrix_ = Matrix4x4::MakeAffinMatrix(uvScale_, uvRotate_, uvPos_);
}

void Model::CreateSkeleton()
{
	Skeleton skeleton;
	skeleton.root = Createjoint(modelData_->rootNode, {}, skeleton.joints);

	for (const Joint& joint : skeleton.joints) {
		skeleton.jointMap.emplace(joint.name, joint.index);
	}
	skeleton_ = std::make_unique<Skeleton>(skeleton);
	UpdateSkeleton();
}

void Model::CreateSkinCluster()
{
	SkinCluter skinCluster;
	// palette用のResourceを確保
	skinCluster.paletteResouce = DirectXBase::CreateBufferResource(sizeof(WellForGPU) * skeleton_->joints.size());
	WellForGPU* mappedPalette = nullptr;
	skinCluster.paletteResouce->Map(0, nullptr, reinterpret_cast<void**>(&mappedPalette));
	skinCluster.mappedPalette = { mappedPalette,skeleton_->joints.size() };
	skinCluster.paletteSrvHandle = DescriptorHeapManager::GetInstance()->GetSRVDescriptorHeap()->GetNewDescriptorHandles();

	// palette用のsrvの作成。StructuredBufferでアクセスできるようにする
	D3D12_SHADER_RESOURCE_VIEW_DESC paletteSRVDesc{};
	paletteSRVDesc.Format = DXGI_FORMAT_UNKNOWN;
	paletteSRVDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	paletteSRVDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	paletteSRVDesc.Buffer.FirstElement = 0;
	paletteSRVDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	paletteSRVDesc.Buffer.NumElements = UINT(skeleton_->joints.size());
	paletteSRVDesc.Buffer.StructureByteStride = sizeof(WellForGPU);
	DirectXBase::GetInstance()->GetDevice()->CreateShaderResourceView(skinCluster.paletteResouce.Get(), &paletteSRVDesc, skinCluster.paletteSrvHandle->cpuHandle);

	// influence用のResourceを確保。頂点ごとにinfluence情報を追加できるようにする
	skinCluster.influenceResouce = DirectXBase::CreateBufferResource(sizeof(VertexInfluence) * modelData_->mesh.verteces.size());
	VertexInfluence* mappedInfluence = nullptr;
	skinCluster.influenceResouce->Map(0, nullptr, reinterpret_cast<void**>(&mappedInfluence));
	std::memset(mappedInfluence, 0, sizeof(VertexInfluence) * modelData_->mesh.verteces.size());
	skinCluster.mappedInfluence = { mappedInfluence,modelData_->mesh.verteces.size() };

	// influence用のVBVを作成
	skinCluster.influenceBufferView.BufferLocation = skinCluster.influenceResouce->GetGPUVirtualAddress();
	skinCluster.influenceBufferView.SizeInBytes = UINT(sizeof(VertexInfluence) * modelData_->mesh.verteces.size());
	skinCluster.influenceBufferView.StrideInBytes = sizeof(VertexInfluence);

	// InverseBindPoseMatrixを格納する場所を作成して、単位行列で埋める
	skinCluster.inverseBindPoseMatrices.resize(skeleton_->joints.size());
	std::generate(skinCluster.inverseBindPoseMatrices.begin(), skinCluster.inverseBindPoseMatrices.end(), Matrix4x4::MakeIdentity4x4);

	// ModelDataを解析してInfluenceを埋める
	for (const std::pair<const std::string, JointWeightData>& jointWeight : modelData_->skinClusterData) {
		std::map<std::string, int32_t>::iterator it = skeleton_->jointMap.find(jointWeight.first);
		if (it == skeleton_->jointMap.end()) {
			continue;
		}
		
		skinCluster.inverseBindPoseMatrices[(*it).second] = jointWeight.second.inverseBindPoseMatrix;
		for (const VertexWeightData& vertexWeight : jointWeight.second.vertexWeights) {
			VertexInfluence& currentInfluence = skinCluster.mappedInfluence[vertexWeight.vertexIndex];
			for (uint32_t index = 0; index < kNumMaxInfluence; index++) {
				if (currentInfluence.weights[index] == 0.0f) {
					currentInfluence.weights[index] = vertexWeight.weight;
					currentInfluence.jointIndices[index] = (*it).second;
					break;
				}
			}
		}
	}

	skinCluter_.reset();
	skinCluter_ = std::make_unique<SkinCluter>(skinCluster);
}

int32_t Model::Createjoint(const NodeData& node, const std::optional<int32_t>& parent, std::vector<Joint>& joints)
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

void Model::UpdateSkeleton()
{
	if (skeleton_) {
		for (Joint& joint : skeleton_->joints) {
			joint.localMatrix = Matrix4x4::MakeAffinMatrix(joint.transform);
			if (joint.parent) {
				joint.skeletonSpaceMatrix = joint.localMatrix * skeleton_->joints[*joint.parent].skeletonSpaceMatrix;
			}
			else {
				joint.skeletonSpaceMatrix = joint.localMatrix;
			}
		}
	}
}

void Model::UpdateSkinAnimation()
{
	for (size_t jointIndex = 0; jointIndex < skeleton_->joints.size(); jointIndex++) {
		assert(jointIndex < skinCluter_->inverseBindPoseMatrices.size());
		skinCluter_->mappedPalette[jointIndex].skeletonSpaceMatrix = skinCluter_->inverseBindPoseMatrices[jointIndex] * skeleton_->joints[jointIndex].skeletonSpaceMatrix;
		skinCluter_->mappedPalette[jointIndex].skeletonSpaceInverseTransposeMatrix = Matrix4x4::Transpose(Matrix4x4::Inverse(skinCluter_->mappedPalette[jointIndex].skeletonSpaceMatrix));
	}
}

void Model::ApplyAnimation()
{
	for (Joint& joint : skeleton_->joints) {
		if (auto it = animation_->nodeAnimations.find(joint.name); it != animation_->nodeAnimations.end()) {
			const NodeAnimation& rootNodeAnimation = (*it).second;
			joint.transform.translate_ = CalculateValue(rootNodeAnimation.translate, animationTime_);
			joint.transform.rotate_ = CalculateValue(rootNodeAnimation.rotate, animationTime_);
			joint.transform.scale_ = CalculateValue(rootNodeAnimation.scale, animationTime_);
		}
	}
}