#pragma once
#include "Matrix4x4.h"
#include "Drawers/DrawManager/DrawManagerBase/DrawManagerBase.h"
#include <wrl.h>
#include <vector>
#include <memory>

class Camera;
class ModelData;
enum class BlendMode;
class GPUParticle;

class DrawParticleManager : public DrawManagerBase
{
public:
	DrawParticleManager();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="particle">パーティクル</param>
	/// <param name="camera">カメラ</param>
	/// <param name="blendMode">ブレンドモード</param>
	void Draw(const GPUParticle& particle,const Camera& camera, BlendMode blendMode);

private:
	/// <summary>
	/// カメラ視点データの設定
	/// </summary>
	/// <param name="camera">カメラ</param>
	void SetPerView(const Camera& camera);
	/// <summary>
	/// カメラ視点情報
	/// </summary>
	class PerView
	{
	public:
		PerView();
		~PerView();
		/// <summary>
		/// カメラ視点データ
		/// </summary>
		struct PerViewData {
			Matrix4x4 viewProjection; // ビュープロジェクション行列
			Matrix4x4 billboardMatrix; // ビルボード行列
		};
		Microsoft::WRL::ComPtr<ID3D12Resource> perViewResource; // リソース
		PerViewData* perViewData; // データ
	};
	std::vector<std::unique_ptr<PerView>> perViews_; // カメラ視点情報の配列
	const ModelData* modelData_; // モデルデータ
};