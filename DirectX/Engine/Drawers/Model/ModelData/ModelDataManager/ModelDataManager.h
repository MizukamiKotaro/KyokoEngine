#pragma once

#include <vector>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Externals/nlohmann/json.hpp"

class ModelData;
class NodeData;
class Animation;
class Vector4;

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

private:
	ModelDataManager() = default;
	~ModelDataManager() = default;
	ModelDataManager(const ModelDataManager&) = delete;
	ModelDataManager& operator=(const ModelDataManager&) = delete;

	void LoadObjFile(const std::string& fileName);

	NodeData ReadNode(aiNode* node);

	void LoadGLTFFile(const std::string& fileName);

	void LoadSkinAnimationFile(const std::string& fileName, const bool& ispmx = false);

	void LoadPMD(const std::string& fileName);

	void LoadMMDMaterials(const std::string& filePath, std::vector<std::pair<int32_t, Vector4>>& colors);

	NodeData ReadNodePMD(uint16_t parentBoneIndex);

	void CreateResources();

	std::string FindPath(const std::string& fileName, const std::string& extension);

	void LoadALL(const std::string& path, const std::string& extension);

private:
	std::vector<std::unique_ptr<ModelData>> modelDatas_;
	std::map<std::string, std::unique_ptr<Animation>> animationMap_;

	const std::string directoryPath_ = "Resources/Object";
	const std::string kObjDirectoryPath_ = "Resources/Object/ObjectModel";
	const std::string kRigidAnimDirectoryPath_ = "Resources/Object/RigidAnimationModel";
	const std::string kSkinningAnimDirectoryPath_ = "Resources/Object/SkinningModel";
};