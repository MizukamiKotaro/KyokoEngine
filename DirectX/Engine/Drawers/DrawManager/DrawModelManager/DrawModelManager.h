#pragma once
#include <vector>
#include <memory>
#include "Drawers/DrawManager/DrawManagerBase/DrawManagerBase.h"
#include "Drawers/DrawManager/Transformation/Transformation.h"

class Camera;
class ModelData;
enum class BlendMode;
class Model;
class RigidAnimationModel;
class SkinningModel;
class BaseModel;
class PMDModel;

/// <summary>
/// モデル用描画マネージャー
/// </summary>
class DrawModelManager : public DrawManagerBase
{
public:
	DrawModelManager();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="camera">カメラ</param>
	/// <param name="blendMode">ブレンドモード</param>
	void Draw(const Model& model,const Camera& camera, BlendMode blendMode);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="camera">カメラ</param>
	/// <param name="blendMode">ブレンドモード</param>
	void Draw(const RigidAnimationModel& model, const Camera& camera, BlendMode blendMode);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="camera">カメラ</param>
	/// <param name="blendMode">ブレンドモード</param>
	void Draw(const SkinningModel& model, const Camera& camera, BlendMode blendMode);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="camera">カメラ</param>
	/// <param name="blendMode">ブレンドモード</param>
	void Draw(const PMDModel& model, const Camera& camera, BlendMode blendMode);
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();
private:
	/// <summary>
	/// 描画共通部分
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="camera">カメラ</param>
	/// <param name="blendMode">ブレンドモード</param>
	/// <param name="vertexBufferView">vertexBufferView</param>
	void Draw(const BaseModel& model, const Camera& camera, BlendMode blendMode, D3D12_VERTEX_BUFFER_VIEW vertexBufferView);
	std::vector<std::unique_ptr<Transformation>> transformations_; // 変換行列データ配列
};