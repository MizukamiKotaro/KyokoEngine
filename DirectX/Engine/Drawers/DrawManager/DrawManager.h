#pragma once
#include <memory>

enum class BlendMode;
class Camera;
class Model;
class RigidAnimationModel;
class SkinningModel;
class PointLight;
class SpotLight;
class GPUParticle;
class PMDModel;
class DrawModelManager;
class DrawLightManager;
class DrawParticleManager;

class DrawManager
{
public:
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static DrawManager* GetInstance();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// リセット
	/// </summary>
	void Reset();
	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

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
	/// 描画
	/// </summary>
	/// <param name="light">ライト</param>
	/// <param name="camera">カメラ</param>
	/// <param name="blendMode">ブレンドモード</param>
	void Draw(const PointLight& light, const Camera& camera, BlendMode blendMode);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="light">ライト</param>
	/// <param name="camera">カメラ</param>
	/// <param name="blendMode">ブレンドモード</param>
	void Draw(const SpotLight& light, const Camera& camera, BlendMode blendMode);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="particle">パーティクル</param>
	/// <param name="camera">カメラ</param>
	/// <param name="blendMode">ブレンドモード</param>
	void Draw(const GPUParticle& particle, const Camera& camera, BlendMode blendMode);
private:
	DrawManager() = default;
	~DrawManager() = default;
	DrawManager(const DrawManager&) = delete;
	const DrawManager& operator=(const DrawManager&) = delete;

	std::unique_ptr<DrawModelManager> drawModelManager_; // モデル用描画マネージャー
	std::unique_ptr<DrawLightManager> drawLightManager_; // ライト用描画マネージャー
	std::unique_ptr<DrawParticleManager> drawParticleManager_; // パーティクル用描画マネージャー
};