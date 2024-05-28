#pragma once
#include "BaseModel/BaseModel.h"

class Camera;

class Model : public BaseModel
{
public:

	// Model(const std::string& fileName);
	// 例)
	// Cubeフォルダ
	//   Cube.obj
	//   Cube.mtl
	// の状態

	/// <summary>
	/// モデルの生成
	/// </summary>
	/// <param name="fileName">.objが入っているフォルダの名前( "Cube" 等)</param>
	Model(const std::string& fileName);

	/// <summary>
	/// モデルの生成
	/// </summary>
	/// <param name="meshHundle">モデルデータのハンドル( ModelDataManager::GetInstance()->LoadObj("Cube") 等)</param>
	Model(const ModelData* modelData);

	void Draw(const Camera& camera, BlendMode blendMode = BlendMode::kBlendModeNormal) const;
};