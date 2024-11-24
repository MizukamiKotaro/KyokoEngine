#pragma once

#include <vector>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Externals/nlohmann/json.hpp"
#include "Vector3.h"
#include "Vector4.h"

class ModelData;
class NodeData;
class Animation;
class ModelDataPMD;

class ModelDataManager 
{
public:

	static ModelDataManager* GetInstance();

	void Initialize();
	void Finalize();

	//uint32_t LoadObj(const std::string& fileName);
	// 例)
	// Cubeフォルダ
	//   Cube.obj
	//   Cube.mtl
	//   hoge.png
	// の状態
	/// <summary>
	/// objファイルの読み込み
	/// </summary>
	/// <param name="fileName">.objが入っているフォルダの名前( "Cube" 等)</param>
	/// <returns>モデルデータのハンドル</returns>
	const ModelData* LoadObj(const std::string& fileName);

	/// <summary>
	/// glTFファイルの読み込み
	/// </summary>
	/// <param name="fileName">.glTFが入っているフォルダの名前( "Cube" 等)</param>
	/// <returns>モデルデータのハンドル</returns>
	const ModelData* LoadGLTF(const std::string& fileName);

	Animation LoadAnimation(const std::string& fileName);

	const ModelData* LoadSkinAnimationModel(const std::string& fileName, const bool& ispmx = false);

	const ModelDataPMD* LoadPMDModelGltf(const std::string& fileName);

private:
	ModelDataManager() = default;
	~ModelDataManager() = default;
	ModelDataManager(const ModelDataManager&) = delete;
	ModelDataManager& operator=(const ModelDataManager&) = delete;

	struct MMDMaterialGLTF
	{
		Vector4 diffuseColor;
		int32_t textureNum;
		Vector3 ambientColor;
		Vector3 specularColor;
		float shinines;
		int32_t sphereTextureNum;
		int32_t toonTextureNum;
	};

	void LoadObjFile(const std::string& fileName);

	NodeData ReadNode(aiNode* node);

	void LoadGLTFFile(const std::string& fileName);

	void LoadSkinAnimationFile(const std::string& fileName, const bool& ispmx = false);

	void LoadPMDGltf(const std::string& fileName);

	void LoadPMD(const std::string& fileName);

	void LoadMMDMaterials(const std::string& filePath, std::vector<std::pair<int32_t, Vector4>>& colors);

	void LoadPMDGltfMaterials(const std::string& filePath, std::vector<MMDMaterialGLTF>& colors);

	NodeData ReadNodePMD(uint16_t parentBoneIndex);

	void CreateResources();

	void CreatePMDResources();

	std::string FindPath(const std::string& fileName, const std::string& extension);

	void LoadALL(const std::string& path, const std::string& extension);

private:
	std::vector<std::unique_ptr<ModelData>> modelDatas_;
	std::vector<std::unique_ptr<ModelDataPMD>> pmdDatas_;
	std::map<std::string, std::unique_ptr<Animation>> animationMap_;

	const std::string directoryPath_ = "Resources/Object";
	const std::string kObjDirectoryPath_ = "Resources/Object/ObjectModel";
	const std::string kRigidAnimDirectoryPath_ = "Resources/Object/RigidAnimationModel";
	const std::string kSkinningAnimDirectoryPath_ = "Resources/Object/SkinningModel";
};