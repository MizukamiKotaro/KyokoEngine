#pragma once
#include "Drawers/DrawManager/DrawManagerBase/DrawManagerBase.h"
#include <vector>
#include <memory>
#include "Drawers/DrawManager/Transformation/Transformation.h"

class Camera;
class ModelData;
enum class BlendMode;
class PointLight;
class SpotLight;

/// <summary>
/// ライト用の描画マネージャー
/// </summary>
class DrawLightManager : public DrawManagerBase
{
public:
	DrawLightManager();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="light">ライト</param>
	/// <param name="camera">カメラ</param>
	/// <param name="blendMode">ブレンドモード</param>
	void Draw(const PointLight& light,const Camera& camera, BlendMode blendMode);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="light">ライト</param>
	/// <param name="camera">カメラ</param>
	/// <param name="blendMode">ブレンドモード</param>
	void Draw(const SpotLight& light, const Camera& camera, BlendMode blendMode);

private:
	std::vector<std::unique_ptr<Transformation>> transformations_; // 変換行列データ配列
	const ModelData* modelData_; // モデルデータ
};