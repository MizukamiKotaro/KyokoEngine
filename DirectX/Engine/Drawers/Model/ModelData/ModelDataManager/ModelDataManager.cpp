#include "ModelDataManager.h"
#include "Engine/Base/DirectXBase/DirectXBase.h"
#include <cassert>
#include "Engine/Base/DebugLog/DebugLog.h"
#include <format>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "TextureManager/TextureManager.h"
#include "ModelData/ModelData.h"
#include "Base/DescriptorHeapManager/DescriptorHandles/DescriptorHandles.h"
#include "GlobalVariables/GlobalVariableComboNames.h"
#include "MMD/MMDModelData/ModelDataPMD.h"

ModelDataManager* ModelDataManager::GetInstance()
{
	static ModelDataManager instance;
	return &instance;
}

void ModelDataManager::Initialize()
{
	LoadALL(kObjDirectoryPath_, ".obj");
	LoadALL(kRigidAnimDirectoryPath_, ".gltf");
	//LoadALL(kSkinningAnimDirectoryPath_, ".gltf");
}

void ModelDataManager::Finalize()
{
	for (uint32_t modelNum = 0; modelNum < static_cast<uint32_t>(modelDatas_.size()); modelNum++) {
		modelDatas_[modelNum]->mesh.vertexResource_->Release();
		modelDatas_[modelNum]->mesh.indexResource_->Release();
	}

	for (uint32_t modelNum = 0; modelNum < static_cast<uint32_t>(pmdDatas_.size()); modelNum++) {
		pmdDatas_[modelNum]->mesh.vertexResource_->Release();
		pmdDatas_[modelNum]->mesh.indexResource_->Release();
	}
}

const ModelData* ModelDataManager::LoadObj(const std::string& fileName)
{
	for (uint32_t modelNum = 0; modelNum < static_cast<uint32_t>(modelDatas_.size()); modelNum++) {

		if (modelDatas_[modelNum]->fileName == fileName) {
			return modelDatas_[modelNum].get();
		}
	}

	LoadObjFile(fileName);

	return modelDatas_.back().get();
}

const ModelData* ModelDataManager::LoadGLTF(const std::string& fileName)
{
	for (uint32_t modelNum = 0; modelNum < static_cast<uint32_t>(modelDatas_.size()); modelNum++) {

		if (modelDatas_[modelNum]->fileName == fileName) {
			return modelDatas_[modelNum].get();
		}
	}

	LoadGLTFFile(fileName);

	return modelDatas_.back().get();
}

Animation ModelDataManager::LoadAnimation(const std::string& fileName)
{
	Animation animation;
	if (animationMap_.find(fileName) != animationMap_.end()) {
		animation = *animationMap_[fileName].get();
		return animation;
	}
	Assimp::Importer importer;
	std::string filePath = FindPath(fileName, ".gltf");
	const aiScene* scene_ = importer.ReadFile(filePath.c_str(), 0);
	assert(scene_->mNumAnimations != 0);
	aiAnimation* animationAssimp = scene_->mAnimations[0];
	animation.duration = float(animationAssimp->mDuration / animationAssimp->mTicksPerSecond);

	for (uint32_t channelIndex = 0; channelIndex < animationAssimp->mNumChannels; channelIndex++) {
		aiNodeAnim* nodeAnimationAssimp = animationAssimp->mChannels[channelIndex];

		NodeAnimation& nodeAnimation = animation.nodeAnimations[nodeAnimationAssimp->mNodeName.C_Str()];

		for (uint32_t positionIndex = 0; positionIndex < nodeAnimationAssimp->mNumPositionKeys; positionIndex++) {
			aiVectorKey& key = nodeAnimationAssimp->mPositionKeys[positionIndex];
			KeyframeVector3 keyframe;
			keyframe.time = float(key.mTime / animationAssimp->mTicksPerSecond);
			keyframe.value = { -key.mValue.x,key.mValue.y ,key.mValue.z };

			nodeAnimation.translate.keyframes.push_back(keyframe);
		}
		for (uint32_t rotateIndex = 0; rotateIndex < nodeAnimationAssimp->mNumRotationKeys; rotateIndex++) {
			aiQuatKey key = nodeAnimationAssimp->mRotationKeys[rotateIndex];
			KeyframeQuaternion keyframe;
			keyframe.time = float(key.mTime / animationAssimp->mTicksPerSecond);
			keyframe.value = { key.mValue.x,-key.mValue.y ,-key.mValue.z, key.mValue.w };

			nodeAnimation.rotate.keyframes.push_back(keyframe);
		}
		for (uint32_t scaleIndex = 0; scaleIndex < nodeAnimationAssimp->mNumScalingKeys; scaleIndex++) {
			aiVectorKey key = nodeAnimationAssimp->mScalingKeys[scaleIndex];
			KeyframeVector3 keyframe;
			keyframe.time = float(key.mTime / animationAssimp->mTicksPerSecond);
			keyframe.value = { key.mValue.x,key.mValue.y ,key.mValue.z };

			nodeAnimation.scale.keyframes.push_back(keyframe);

		}
		nodeAnimation.translate.currentFrame = 0;
		nodeAnimation.rotate.currentFrame = 0;
		nodeAnimation.scale.currentFrame = 0;
	}

	animationMap_[fileName] = std::make_unique<Animation>(animation);
	return animation;
}

const ModelData* ModelDataManager::LoadSkinAnimationModel(const std::string& fileName, const bool& ispmx)
{
	for (uint32_t modelNum = 0; modelNum < static_cast<uint32_t>(modelDatas_.size()); modelNum++) {

		if (modelDatas_[modelNum]->fileName == fileName) {
			return modelDatas_[modelNum].get();
		}
	}

	LoadSkinAnimationFile(fileName, ispmx);

	return modelDatas_.back().get();
}

const ModelDataPMD* ModelDataManager::LoadPMDModelGltf(const std::string& fileName)
{
	for (uint32_t modelNum = 0; modelNum < static_cast<uint32_t>(pmdDatas_.size()); modelNum++) {
		if (pmdDatas_[modelNum]->fileName == fileName) {
			return pmdDatas_[modelNum].get();
		}
	}


	LoadPMDGltf(fileName);

	return pmdDatas_.back().get();
}

void ModelDataManager::LoadObjFile(const std::string& fileName)
{
	GlobalVariableComboNames* combo = GlobalVariableComboNames::GetInstance();
	combo->AddComboName(ComboNameType::kOBJ, fileName);
	// 1. 中で必要となる変数の宣言
	modelDatas_.push_back(std::make_unique<ModelData>());; // 構築するModelData

	modelDatas_.back()->fileName = fileName;
	
	std::string filePath = FindPath(fileName, ".obj");

	Assimp::Importer importer;
	const aiScene* scene_ = importer.ReadFile(filePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
	assert(scene_->HasMeshes());
	uint32_t vertexNum = 0;
	TextureManager* texMa = TextureManager::GetInstance();
	const Texture* tex = nullptr;
	// meshを解析する
	for (uint32_t meshIndex = 0; meshIndex < scene_->mNumMeshes; meshIndex++) {
		aiMesh* mesh = scene_->mMeshes[meshIndex];
		assert(mesh->HasNormals()); // 法線がないmeshは非対応

		const aiMaterial* material = scene_->mMaterials[mesh->mMaterialIndex];
		aiColor4D diffuseColor;
		Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
		int32_t texNum = -1;
		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor)) {
			color = { diffuseColor.r,diffuseColor.g,diffuseColor.b,diffuseColor.a };
		}
		if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
			aiString textureFilePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
			std::string texFilePath;
			if (textureFilePath.length > 0) {
				texFilePath = textureFilePath.C_Str();
				std::filesystem::path filePathName(texFilePath);
				texFilePath = filePathName.filename().string();
				tex = texMa->LoadTexture(texFilePath);
				texNum = int32_t(tex->handles_->no);
			}
		}

		// vertexを解析
		//modelDatas_.back()->mesh.verteces.resize(mesh->mNumVertices);
		for (uint32_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; vertexIndex++) {
			aiVector3D& position = mesh->mVertices[vertexIndex];
			aiVector3D& normal = mesh->mNormals[vertexIndex];
			aiVector3D texcoord = {};
			if (mesh->HasTextureCoords(0)) {
				texcoord = mesh->mTextureCoords[0][vertexIndex];
			}

			modelDatas_.back()->mesh.verteces.push_back(
				VertexData{ { -position.x,position.y,position.z,1.0f },{ texcoord.x,texcoord.y }, { -normal.x,normal.y,normal.z },color,texNum });
		}


		// indexを解析
		for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++) {
			aiFace& face = mesh->mFaces[faceIndex];
			assert(face.mNumIndices == 3);
			for (uint32_t element = 0; element < face.mNumIndices; element++) {
				modelDatas_.back()->mesh.indices.push_back(face.mIndices[element] + vertexNum);
			}
		}
		vertexNum += mesh->mNumVertices;
	}
	// rootNodeの解析
	modelDatas_.back()->rootNode = ReadNode(scene_->mRootNode);

	bool isLoadTexture = false;
	// materialを解析する
	for (uint32_t materialIndex = 0; materialIndex < scene_->mNumMaterials; materialIndex++) {
		aiMaterial* material = scene_->mMaterials[materialIndex];
		if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
			aiString textureFilePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
			std::string texFilePath;
			if (textureFilePath.length > 0) {
				texFilePath = textureFilePath.C_Str();
				std::filesystem::path filePathName(texFilePath);
				texFilePath = filePathName.filename().string();
			}
			else {
				texFilePath = "white.png";
			}
			isLoadTexture = true;
			modelDatas_.back()->texture = TextureManager::GetInstance()->LoadTexture(texFilePath);
		}
	}

	if (!isLoadTexture) {
		std::string texFilePath = "white.png";
		modelDatas_.back()->texture = TextureManager::GetInstance()->LoadTexture(texFilePath);
	}

	CreateResources();
}

NodeData ModelDataManager::ReadNode(aiNode* node)
{
	NodeData result;
	aiVector3D scale, translate;
	aiQuaternion rotate;
	node->mTransformation.Decompose(scale, rotate, translate);
	result.transform.scale_ = { scale.x,scale.y,scale.z };
	result.transform.rotate_ = { rotate.x,-rotate.y,-rotate.z,rotate.w };
	result.transform.translate_ = { -translate.x,translate.y,translate.z };
	result.localMatrix = Matrix4x4::MakeAffinMatrix(result.transform);

	result.name = node->mName.C_Str();
	result.children.resize(node->mNumChildren);
	for (uint32_t childIndex = 0; childIndex < node->mNumChildren; childIndex++) {
		result.children[childIndex] = ReadNode(node->mChildren[childIndex]);
	}

	return result;
}

void ModelDataManager::LoadGLTFFile(const std::string& fileName)
{
	GlobalVariableComboNames* combo = GlobalVariableComboNames::GetInstance();
	combo->AddComboName(ComboNameType::kRigidAnimationModel, fileName);
	// 1. 中で必要となる変数の宣言
	modelDatas_.push_back(std::make_unique<ModelData>());; // 構築するModelData

	modelDatas_.back()->fileName = fileName;

	Assimp::Importer importer;
	std::string filePath = FindPath(fileName, ".gltf");
	const aiScene* scene_ = importer.ReadFile(filePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
	assert(scene_->HasMeshes());

	uint32_t vertexNum = 0;
	TextureManager* texMa = TextureManager::GetInstance();
	const Texture* tex = nullptr;
	// meshを解析する
	for (uint32_t meshIndex = 0; meshIndex < scene_->mNumMeshes; meshIndex++) {
		aiMesh* mesh = scene_->mMeshes[meshIndex];
		assert(mesh->HasNormals()); // 法線がないmeshは非対応

		const aiMaterial* material = scene_->mMaterials[mesh->mMaterialIndex];
		aiColor4D diffuseColor;
		Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
		int32_t texNum = -1;
		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor)) {
			color = { diffuseColor.r,diffuseColor.g,diffuseColor.b,diffuseColor.a };
		}
		if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
			aiString textureFilePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
			std::string texFilePath;
			if (textureFilePath.length > 0) {
				texFilePath = textureFilePath.C_Str();
				std::filesystem::path filePathName(texFilePath);
				texFilePath = filePathName.filename().string();
				tex = texMa->LoadTexture(texFilePath);
				texNum = int32_t(tex->handles_->no);
			}
		}

		// vertexを解析
		//modelDatas_.back()->mesh.verteces.resize(mesh->mNumVertices);
		for (uint32_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; vertexIndex++) {
			aiVector3D& position = mesh->mVertices[vertexIndex];
			aiVector3D& normal = mesh->mNormals[vertexIndex];
			aiVector3D texcoord = {};
			if (mesh->HasTextureCoords(0)) {
				texcoord = mesh->mTextureCoords[0][vertexIndex];
			}

			modelDatas_.back()->mesh.verteces.push_back(
				VertexData{ { -position.x,position.y,position.z,1.0f },{ texcoord.x,texcoord.y }, { -normal.x,normal.y,normal.z },color,texNum });
		}

		// indexを解析
		for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++) {
			aiFace& face = mesh->mFaces[faceIndex];
			assert(face.mNumIndices == 3);
			for (uint32_t element = 0; element < face.mNumIndices; element++) {
				modelDatas_.back()->mesh.indices.push_back(face.mIndices[element] + vertexNum);
			}
		}
		vertexNum += mesh->mNumVertices;
	}
	// rootNodeの解析
	modelDatas_.back()->rootNode = ReadNode(scene_->mRootNode);

	bool isLoadTexture = false;
	// materialを解析する
	for (uint32_t materialIndex = 0; materialIndex < scene_->mNumMaterials; materialIndex++) {
		aiMaterial* material = scene_->mMaterials[materialIndex];
		if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
			aiString textureFilePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
			std::string texFilePath;
			if (textureFilePath.length > 0) {
				texFilePath = textureFilePath.C_Str();
				std::filesystem::path filePathName(texFilePath);
				texFilePath = filePathName.filename().string();
			}
			else {
				texFilePath = "white.png";
			}
			isLoadTexture = true;
			modelDatas_.back()->texture = TextureManager::GetInstance()->LoadTexture(texFilePath);
		}
	}

	if (!isLoadTexture) {
		std::string texFilePath = "white.png";
		modelDatas_.back()->texture = TextureManager::GetInstance()->LoadTexture(texFilePath);
	}

	CreateResources();
}

void ModelDataManager::LoadSkinAnimationFile(const std::string& fileName, const bool& ispmx)
{
	GlobalVariableComboNames* combo = GlobalVariableComboNames::GetInstance();
	combo->AddComboName(ComboNameType::kSkinningModel, fileName);
	// 1. 中で必要となる変数の宣言
	modelDatas_.push_back(std::make_unique<ModelData>());; // 構築するModelData

	modelDatas_.back()->fileName = fileName;

	Assimp::Importer importer;
	std::string filePath = FindPath(fileName, ".gltf");
	const aiScene* scene_ = importer.ReadFile(filePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
	std::vector<std::pair<int32_t, Vector4>> colors;
	if (ispmx) {
		LoadMMDMaterials(filePath, colors);
	}
	assert(scene_->HasMeshes());

	uint32_t vertexNum = 0;
	TextureManager* texMa = TextureManager::GetInstance();
	const Texture* tex = nullptr;
	// meshを解析する
	for (uint32_t meshIndex = 0; meshIndex < scene_->mNumMeshes; meshIndex++) {
		aiMesh* mesh = scene_->mMeshes[meshIndex];
		assert(mesh->HasNormals()); // 法線がないmeshは非対応

		const aiMaterial* material = scene_->mMaterials[mesh->mMaterialIndex];
		aiColor4D diffuseColor;
		Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
		int32_t texNum = -1;
		if (ispmx && uint32_t(colors.size()) > meshIndex) {
			color = colors[meshIndex].second;
			texNum = colors[meshIndex].first;
		}
		else if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
			aiString textureFilePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
			std::string texFilePath;
			if (textureFilePath.length > 0) {
				texFilePath = textureFilePath.C_Str();
				std::filesystem::path filePathName(texFilePath);
				texFilePath = filePathName.filename().string();
				tex = texMa->LoadTexture(texFilePath);
				texNum = int32_t(tex->handles_->no);
			}
		}

		// vertexを解析
		//modelDatas_.back()->mesh.verteces.resize(mesh->mNumVertices);
		for (uint32_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; vertexIndex++) {
			aiVector3D& position = mesh->mVertices[vertexIndex];
			aiVector3D& normal = mesh->mNormals[vertexIndex];
			aiVector3D texcoord = {};
			if (mesh->HasTextureCoords(0)) {
				texcoord = mesh->mTextureCoords[0][vertexIndex];
			}

			VertexData vData;
			vData.vertexPos = { -position.x,position.y,position.z,1.0f };
			vData.texcoord = { texcoord.x,texcoord.y };
			vData.normal = { -normal.x,normal.y,normal.z };
			vData.diffuseColor = color;
			vData.textureNum = texNum;
			
			modelDatas_.back()->mesh.verteces.push_back(vData);
		}

		// indexを解析
		for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++) {
			aiFace& face = mesh->mFaces[faceIndex];
			assert(face.mNumIndices == 3);
			for (uint32_t element = 0; element < face.mNumIndices; element++) {
				modelDatas_.back()->mesh.indices.push_back(face.mIndices[element] + vertexNum);
			}
		}

		// boneの解析
		for (uint32_t boneIndex = 0; boneIndex < mesh->mNumBones; boneIndex++) {
			aiBone* bone = mesh->mBones[boneIndex];
			std::string jointName = bone->mName.C_Str();
			JointWeightData& jointWeightData = modelDatas_.back()->skinClusterData[jointName];

			aiMatrix4x4 bindPoseMatrixAssimp = bone->mOffsetMatrix.Inverse();
			aiVector3D scale, translate;
			aiQuaternion rotate;
			bindPoseMatrixAssimp.Decompose(scale, rotate, translate);
			Matrix4x4 bindPoseMatrix = Matrix4x4::MakeAffinMatrix(Vector3{ scale.x,scale.y,scale.z },
				Quaternion{ rotate.x,-rotate.y,-rotate.z,rotate.w }, Vector3{ -translate.x,translate.y,translate.z });
			jointWeightData.inverseBindPoseMatrix = Matrix4x4::Inverse(bindPoseMatrix);

			for (uint32_t weightIndex = 0; weightIndex < bone->mNumWeights; weightIndex++) {
				jointWeightData.vertexWeights.push_back({ bone->mWeights[weightIndex].mWeight, bone->mWeights[weightIndex].mVertexId + vertexNum });
			}
		}
		vertexNum += mesh->mNumVertices;
	}
	// rootNodeの解析
	modelDatas_.back()->rootNode = ReadNode(scene_->mRootNode);

	bool isLoadTexture = false;
	// materialを解析する
	for (uint32_t materialIndex = 0; materialIndex < scene_->mNumMaterials; materialIndex++) {
		aiMaterial* material = scene_->mMaterials[materialIndex];
		if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
			aiString textureFilePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
			std::string texFilePath;
			if (textureFilePath.length > 0) {
				texFilePath = textureFilePath.C_Str();
				std::filesystem::path filePathName(texFilePath);
				texFilePath = filePathName.filename().string();
			}
			else {
				texFilePath = "white.png";
			}
			isLoadTexture = true;
			modelDatas_.back()->texture = TextureManager::GetInstance()->LoadTexture(texFilePath);
		}
	}

	if (!isLoadTexture) {
		std::string texFilePath = "white.png";
		modelDatas_.back()->texture = TextureManager::GetInstance()->LoadTexture(texFilePath);
	}

	CreateResources();
}

void ModelDataManager::LoadPMDGltf(const std::string& fileName)
{
	/*GlobalVariableComboNames* combo = GlobalVariableComboNames::GetInstance();
	combo->AddComboName(ComboNameType::kPMD, fileName);*/
	// 1. 中で必要となる変数の宣言
	pmdDatas_.push_back(std::make_unique<ModelDataPMD>());; // 構築するModelData

	pmdDatas_.back()->fileName = fileName;

	Assimp::Importer importer;
	std::string filePath = FindPath(fileName, ".gltf");
	const aiScene* scene_ = importer.ReadFile(filePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
	std::vector<MMDMaterialGLTF> colors;
	LoadPMDGltfMaterials(filePath, colors);

	assert(scene_->HasMeshes());

	uint32_t vertexNum = 0;
	// meshを解析する
	for (uint32_t meshIndex = 0; meshIndex < scene_->mNumMeshes; meshIndex++) {
		aiMesh* mesh = scene_->mMeshes[meshIndex];
		assert(mesh->HasNormals()); // 法線がないmeshは非対応

		// vertexを解析
		for (uint32_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; vertexIndex++) {
			aiVector3D& position = mesh->mVertices[vertexIndex];
			aiVector3D& normal = mesh->mNormals[vertexIndex];
			aiVector3D texcoord = {};
			if (mesh->HasTextureCoords(0)) {
				texcoord = mesh->mTextureCoords[0][vertexIndex];
			}

			VertexDataPMD vData;
			vData.vertexPos = { -position.x,position.y,position.z,1.0f };
			vData.texcoord = { texcoord.x,texcoord.y };
			vData.normal = { -normal.x,normal.y,normal.z };
			vData.diffuseColor = colors[meshIndex].diffuseColor;
			vData.ambientColor = colors[meshIndex].ambientColor;
			vData.specularColor = colors[meshIndex].specularColor;
			vData.textureNum = colors[meshIndex].textureNum;

			vData.shinines = colors[meshIndex].shinines;
			vData.sphereTextureNum = colors[meshIndex].sphereTextureNum;
			vData.toonTextureNum = colors[meshIndex].toonTextureNum;

			pmdDatas_.back()->mesh.verteces.push_back(vData);
		}

		// indexを解析
		for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++) {
			aiFace& face = mesh->mFaces[faceIndex];
			assert(face.mNumIndices == 3);
			for (uint32_t element = 0; element < face.mNumIndices; element++) {
				pmdDatas_.back()->mesh.indices.push_back(face.mIndices[element] + vertexNum);
			}
		}

		// boneの解析
		for (uint32_t boneIndex = 0; boneIndex < mesh->mNumBones; boneIndex++) {
			aiBone* bone = mesh->mBones[boneIndex];
			std::string jointName = bone->mName.C_Str();
			JointWeightData& jointWeightData = pmdDatas_.back()->skinClusterData[jointName];

			aiMatrix4x4 bindPoseMatrixAssimp = bone->mOffsetMatrix.Inverse();
			aiVector3D scale, translate;
			aiQuaternion rotate;
			bindPoseMatrixAssimp.Decompose(scale, rotate, translate);
			Matrix4x4 bindPoseMatrix = Matrix4x4::MakeAffinMatrix(Vector3{ scale.x,scale.y,scale.z },
				Quaternion{ rotate.x,-rotate.y,-rotate.z,rotate.w }, Vector3{ -translate.x,translate.y,translate.z });
			jointWeightData.inverseBindPoseMatrix = Matrix4x4::Inverse(bindPoseMatrix);

			for (uint32_t weightIndex = 0; weightIndex < bone->mNumWeights; weightIndex++) {
				jointWeightData.vertexWeights.push_back({ bone->mWeights[weightIndex].mWeight, bone->mWeights[weightIndex].mVertexId + vertexNum });
			}
		}
		vertexNum += mesh->mNumVertices;
	}
	// rootNodeの解析
	pmdDatas_.back()->rootNode = ReadNode(scene_->mRootNode);

	CreatePMDResources();
}

void ModelDataManager::LoadPMD(const std::string& fileName)
{// 1. 中で必要となる変数の宣言
	modelDatas_.push_back(std::make_unique<ModelData>());; // 構築するModelData

	modelDatas_.back()->fileName = fileName;

	Assimp::Importer importer;
	std::string filePath = directoryPath_ + "/" + fileName + "/" + fileName + ".pmd";

	std::ifstream file(filePath, std::ios::binary);
	assert(file.is_open());


	// シグネチャやヘッダー分飛ばす
	file.seekg(283, std::ios::cur);
	//struct PMDHeader {
	//	float version;  // バージョン番号
	//	char modelName[20];  // モデル名
	//	char comment[256];   // コメント
	//};
	//PMDHeader header;
	//file.read(reinterpret_cast<char*>(&header), sizeof(PMDHeader));

	struct PMDVertex {
		float position[3];
		float normal[3];
		float uv[2];
		uint16_t boneIndex[2];  // ボーンのインデックス
		uint8_t boneWeight;     // ボーンウェイト
		uint8_t edgeFlag;       // エッジ表示の有無
	};

	std::vector<PMDVertex> vertices;
	uint32_t vertexCount;
	file.read(reinterpret_cast<char*>(&vertexCount), sizeof(vertexCount));
	vertices.resize(vertexCount);
	file.read(reinterpret_cast<char*>(vertices.data()), vertexCount * sizeof(PMDVertex));

	std::vector<uint16_t> indices;
	uint32_t indexCount;
	file.read(reinterpret_cast<char*>(&indexCount), sizeof(indexCount));
	indices.resize(indexCount);
	file.read(reinterpret_cast<char*>(indices.data()), indexCount * sizeof(uint16_t));

	struct PMDMaterial {
		float diffuse[3];
		float alpha;
		float specularPower;
		float specular[3];
		float ambient[3];
		uint8_t toonIndex;
		uint8_t edgeFlag;
		uint32_t indexCount;
		char textureFileName[20];
	};

	std::vector<PMDMaterial> materials;
	uint32_t materialCount;
	file.read(reinterpret_cast<char*>(&materialCount), sizeof(materialCount));
	materials.resize(materialCount);
	file.read(reinterpret_cast<char*>(materials.data()), materialCount * sizeof(PMDMaterial));

	struct PMDBone {
		char boneName[20];
		uint16_t parentBoneIndex;
		uint16_t tailBoneIndex;
		uint8_t boneType;
		uint16_t ikParentBoneIndex;
		float position[3];
	};

	std::vector<PMDBone> bones;
	uint16_t boneCount;
	file.read(reinterpret_cast<char*>(&boneCount), sizeof(boneCount));
	bones.resize(boneCount);
	file.read(reinterpret_cast<char*>(bones.data()), boneCount * sizeof(PMDBone));

	for (const auto& vertex : vertices) {
		VertexData vData;
		vData.vertexPos = { vertex.position[0], vertex.position[1], vertex.position[2], 1.0f };
		vData.texcoord = { vertex.uv[0], vertex.uv[1] };
		vData.normal = { vertex.normal[0], vertex.normal[1], vertex.normal[2] };



		modelDatas_.back()->mesh.verteces.push_back(vData);
	}

	for (const auto& index : indices) {
		modelDatas_.back()->mesh.indices.push_back(uint32_t(index));
	}

	uint32_t currentMaterialIndex = 0;
	for (const auto& material : materials) {
		int32_t texNum = int32_t(TextureManager::GetInstance()->LoadTexture(material.textureFileName)->handles_->no);
		for (uint32_t i = 0; i < material.indexCount; i++) {
			uint32_t vertexIndex = indices[i]; // インデックスから頂点を取得
			modelDatas_.back()->mesh.verteces[vertexIndex].diffuseColor = { material.diffuse[0],material.diffuse[1] ,material.diffuse[2],1.0f };
			modelDatas_.back()->mesh.verteces[vertexIndex].textureNum = texNum;
		}
		currentMaterialIndex++;
	}

	uint16_t boneIndex = 0;
	// ボーンデータをPMD形式で読み込む
	for (const auto& bone : bones) {
		std::string boneName(bone.boneName);
		JointWeightData& jointWeightData = modelDatas_.back()->skinClusterData[boneName];

		// ボーンのバインドポーズ行列を作成
		Vector3 scale = { 1.0f, 1.0f, 1.0f }; // PMDではスケールは通常1.0
		Quaternion rotate = Quaternion::Identity();
		Vector3 translate = { bone.position[0], bone.position[1], bone.position[2] };

		Matrix4x4 bindPoseMatrix = Matrix4x4::MakeAffinMatrix(scale, rotate, translate);
		jointWeightData.inverseBindPoseMatrix = Matrix4x4::Inverse(bindPoseMatrix);

		// ボーンウェイトの処理はPMDファイルに合わせる必要があります
		// ウェイトデータは事前に読み込んだ頂点データから抽出
		for (uint32_t i = 0; i < vertices.size(); ++i) {
			if (vertices[i].boneIndex[0] == boneIndex) {
				jointWeightData.vertexWeights.push_back({ vertices[i].boneWeight / 100.0f, i });
			}
		}
		boneIndex++;
	}


	CreateResources();
}

NodeData ModelDataManager::ReadNodePMD(uint16_t parentBoneIndex) {
	NodeData result;
	parentBoneIndex;
	//// 親ボーンインデックスが一致するボーンを探す
	//for (const auto& bone : bones) {
	//	if (bone.parentBoneIndex == parentBoneIndex) {
	//		result.name = std::string(bone.boneName);
	//		result.transform.translate_ = { bone.position[0], bone.position[1], bone.position[2] };
	//		result.transform.scale_ = { 1.0f, 1.0f, 1.0f };
	//		result.transform.rotate_ = { 0.0f, 0.0f, 0.0f, 1.0f }; // PMDでは回転は通常初期値

	//		result.localMatrix = Matrix4x4::MakeAffinMatrix(result.transform);

	//		// 子ノード（ボーン）を再帰的に読み込む
	//		for (uint16_t childBoneIndex = 0; childBoneIndex < boneCount; ++childBoneIndex) {
	//			if (bones[childBoneIndex].parentBoneIndex == boneIndex) {
	//				result.children.push_back(ReadNodePMD(childBoneIndex));
	//			}
	//		}
	//	}
	//}
	return result;
}

void ModelDataManager::LoadMMDMaterials(const std::string& filePath, std::vector<std::pair<int32_t, Vector4>>& colors)
{
	std::ifstream ifs;
	ifs.open(filePath);

	if (ifs.fail()) {
		assert(0);
		return;
	}

	nlohmann::json root;
	ifs >> root;
	ifs.close();
	nlohmann::json::iterator itGroup = root.find("materials");
	assert(itGroup != root.end());

	for (nlohmann::json::iterator itItem = itGroup->begin(); itItem != itGroup->end(); ++itItem) {
		nlohmann::json::iterator it = itItem->find("extras")->find("mmd_material")->find("diffuse_color");
		std::pair<int32_t, Vector4> result;
		result.second = { it->at(0), it->at(1), it->at(2),1.0f };

		it = itItem->find("extras")->find("mmd_material")->find("comment");
		std::string path = it->get<std::string>();
		if (path.length() > 0) {
			result.first = int32_t(TextureManager::GetInstance()->LoadTexture(path)->handles_->no);
		}
		else {
			result.first = -1;
		}

		colors.push_back(result);
	}
}

void ModelDataManager::LoadPMDGltfMaterials(const std::string& filePath, std::vector<MMDMaterialGLTF>& colors)
{
	std::ifstream ifs;
	ifs.open(filePath);

	if (ifs.fail()) {
		assert(0);
		return;
	}

	nlohmann::json root;
	ifs >> root;
	ifs.close();
	nlohmann::json::iterator itGroup = root.find("materials");
	assert(itGroup != root.end());

	for (nlohmann::json::iterator itItem = itGroup->begin(); itItem != itGroup->end(); ++itItem) {
		nlohmann::json::iterator i = itItem->find("extras")->find("mmd_material");
		nlohmann::json::iterator it = i->find("diffuse_color");
		MMDMaterialGLTF result;
		Vector3 color = { it->at(0), it->at(1), it->at(2) };
		it = i->find("alpha");
		result.diffuseColor = { color.x, color.y, color.z, float(it->get<double>())};

		it = i->find("ambient_color");
		result.ambientColor = { it->at(0), it->at(1), it->at(2) };

		it = i->find("specular_color");
		result.specularColor = { it->at(0), it->at(1), it->at(2) };

		it = i->find("shininess");
		result.shinines = float(it->get<double>());

		it = i->find("shared_toon_texture");
		int32_t n = it->get<int32_t>();
		if (n == 0) {
			result.toonTextureNum = -1;
		}
		else {
			if (n < 10) {
				result.toonTextureNum = int32_t(TextureManager::GetInstance()->LoadTexture("toon0" + std::to_string(n) + ".bmp")->handles_->no);
			}
			else {
				result.toonTextureNum = int32_t(TextureManager::GetInstance()->LoadTexture("toon" + std::to_string(n) + ".bmp")->handles_->no);
			}
		}
		
		it = i->find("texture");
		std::string path;
		if (it == i->end()) {
			result.textureNum = -1;
		}
		else {
			path = it->get<std::string>();
			result.textureNum = int32_t(TextureManager::GetInstance()->LoadTexture(path)->handles_->no);
		}

		it = i->find("sphere");
		result.sphereTextureNum = -1;
		/*if (it == i->end()) {
			result.sphereTextureNum = -1;
		}
		else {
			path = it->get<std::string>();
			result.sphereTextureNum = int32_t(TextureManager::GetInstance()->LoadTexture(path)->handles_->no);
		}*/

		colors.push_back(result);
	}
}

void ModelDataManager::CreateResources()
{
	modelDatas_.back()->mesh.indexResource_ = DirectXBase::CreateBufferResource(sizeof(uint32_t) * modelDatas_.back()->mesh.indices.size());

	modelDatas_.back()->mesh.indexBufferView_.BufferLocation = modelDatas_.back()->mesh.indexResource_->GetGPUVirtualAddress();
	modelDatas_.back()->mesh.indexBufferView_.SizeInBytes = UINT(sizeof(uint32_t) * modelDatas_.back()->mesh.indices.size());
	modelDatas_.back()->mesh.indexBufferView_.Format = DXGI_FORMAT_R32_UINT;

	modelDatas_.back()->mesh.indexResource_->Map(0, nullptr, reinterpret_cast<void**>(&modelDatas_.back()->mesh.mappedIndex));
	std::memcpy(modelDatas_.back()->mesh.mappedIndex, modelDatas_.back()->mesh.indices.data(), sizeof(uint32_t) * modelDatas_.back()->mesh.indices.size());

	modelDatas_.back()->mesh.vertexResource_ = DirectXBase::CreateBufferResource(sizeof(VertexData) * modelDatas_.back()->mesh.verteces.size());

	//VertexBufferViewを作成する
	//頂点バッファビューを作成する
	//リソースの先頭のアドレスから使う
	modelDatas_.back()->mesh.vertexBufferView_.BufferLocation = modelDatas_.back()->mesh.vertexResource_->GetGPUVirtualAddress();
	//使用するリソースのサイズは頂点3つ分のサイズ
	modelDatas_.back()->mesh.vertexBufferView_.SizeInBytes = UINT(sizeof(VertexData) * modelDatas_.back()->mesh.verteces.size());
	//頂点当たりのサイズ
	modelDatas_.back()->mesh.vertexBufferView_.StrideInBytes = sizeof(VertexData);

	//Resourceにデータを書き込む
	//頂点リソースにデータを書き込む
	//書き込むためのアドレスを取得
	modelDatas_.back()->mesh.vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&modelDatas_.back()->mesh.vertexData_));
	std::memcpy(modelDatas_.back()->mesh.vertexData_, modelDatas_.back()->mesh.verteces.data(), sizeof(VertexData) * modelDatas_.back()->mesh.verteces.size());
}

void ModelDataManager::CreatePMDResources()
{
	pmdDatas_.back()->mesh.indexResource_ = DirectXBase::CreateBufferResource(sizeof(uint32_t) * pmdDatas_.back()->mesh.indices.size());

	pmdDatas_.back()->mesh.indexBufferView_.BufferLocation = pmdDatas_.back()->mesh.indexResource_->GetGPUVirtualAddress();
	pmdDatas_.back()->mesh.indexBufferView_.SizeInBytes = UINT(sizeof(uint32_t) * pmdDatas_.back()->mesh.indices.size());
	pmdDatas_.back()->mesh.indexBufferView_.Format = DXGI_FORMAT_R32_UINT;

	pmdDatas_.back()->mesh.indexResource_->Map(0, nullptr, reinterpret_cast<void**>(&pmdDatas_.back()->mesh.mappedIndex));
	std::memcpy(pmdDatas_.back()->mesh.mappedIndex, pmdDatas_.back()->mesh.indices.data(), sizeof(uint32_t) * pmdDatas_.back()->mesh.indices.size());

	pmdDatas_.back()->mesh.vertexResource_ = DirectXBase::CreateBufferResource(sizeof(VertexDataPMD) * pmdDatas_.back()->mesh.verteces.size());

	//VertexBufferViewを作成する
	//頂点バッファビューを作成する
	//リソースの先頭のアドレスから使う
	pmdDatas_.back()->mesh.vertexBufferView_.BufferLocation = pmdDatas_.back()->mesh.vertexResource_->GetGPUVirtualAddress();
	//使用するリソースのサイズは頂点3つ分のサイズ
	pmdDatas_.back()->mesh.vertexBufferView_.SizeInBytes = UINT(sizeof(VertexDataPMD) * pmdDatas_.back()->mesh.verteces.size());
	//頂点当たりのサイズ
	pmdDatas_.back()->mesh.vertexBufferView_.StrideInBytes = sizeof(VertexDataPMD);

	//Resourceにデータを書き込む
	//頂点リソースにデータを書き込む
	//書き込むためのアドレスを取得
	pmdDatas_.back()->mesh.vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&pmdDatas_.back()->mesh.vertexData_));
	std::memcpy(pmdDatas_.back()->mesh.vertexData_, pmdDatas_.back()->mesh.verteces.data(), sizeof(VertexDataPMD) * pmdDatas_.back()->mesh.verteces.size());
}

std::string ModelDataManager::FindPath(const std::string& fileName, const std::string& extension)
{
	std::filesystem::path filePathNamea(fileName + extension);
	std::string filePath = filePathNamea.filename().string();

	std::filesystem::path dir(directoryPath_);

	for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(dir)) {
		if (entry.is_regular_file() && entry.path().filename().string() == filePath) {
			return entry.path().string();
		}
	}
	return directoryPath_ + fileName + extension;
}

void ModelDataManager::LoadALL(const std::string& path, const std::string& extension) 
{
	std::filesystem::path dir(path);
	for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(dir)) {
		const std::filesystem::path& filePath = entry.path();
		if (filePath.extension() == extension) {
			std::string fileName = filePath.stem().string();
			if (path == kObjDirectoryPath_) {
				LoadObj(fileName);
			}
			else if (path == kRigidAnimDirectoryPath_) {
				LoadGLTF(fileName);
			}
			else if (path == kSkinningAnimDirectoryPath_) {
				LoadSkinAnimationModel(fileName, true);
				LoadAnimation(fileName);
				LoadPMDGltf(fileName);
			}
		}
	}
}