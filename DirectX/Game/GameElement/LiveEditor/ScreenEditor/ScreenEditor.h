#pragma once
#include "Model.h"
#include <memory>
#include "Sprite.h"
#include "PostEffect/PostEffect.h"
#include "GameElement/BaseStageObject/BaseStageObject.h"

class Camera;

/// <summary>
/// スクリーンエディター
/// </summary>
class ScreenEditor : public BaseStageObject
{
public:
	/// <summary>
	/// 通常コンストラクタ
	/// </summary>
	/// <param name="mainName">メインの名前</param>
	/// <param name="name">名前</param>
	/// <param name="no">ナンバー</param>
	ScreenEditor(const std::string& mainName, const std::string& name, uint32_t no);
	/// <summary>
	/// マルチスクリーン用コンストラクタ
	/// </summary>
	/// <param name="mainName">メインの名前</param>
	/// <param name="name">名前</param>
	/// <param name="treeName">ツリー名</param>
	/// <param name="no">ナンバー</param>
	ScreenEditor(const std::string& mainName, const std::string& name, const std::string& treeName, uint32_t no);
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="time">デルタタイム</param>
	void Update(float time) override;
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(const Camera& camera) override;
	/// <summary>
	/// 書き込み前処理
	/// </summary>
	void PreDrawScene();
	/// <summary>
	/// 書き込み後処理
	/// </summary>
	void PostDrawScene();
	/// <summary>
	/// 描画したいテクスチャのGPUハンドル
	/// </summary>
	/// <param name="srvGPUDescriptorHandle">GPUハンドル</param>
	void SetGPUHandle(D3D12_GPU_DESCRIPTOR_HANDLE srvGPUDescriptorHandle);
	/// <summary>
	/// 書き込まれたもののテクスチャGPUハンドルの取得
	/// </summary>
	/// <returns>GPUハンドル</returns>
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle();
	/// <summary>
	/// リセット
	/// </summary>
	void Reset();
	/// <summary>
	/// カメラの取得
	/// </summary>
	/// <returns>カメラ</returns>
	const Camera& GetCamera() const { return *camera_.get(); }

private:
	/// <summary>
	/// グローバル変数の設定
	/// </summary>
	void SetGlobalVariable() override;
	/// <summary>
	/// グローバル変数の適用
	/// </summary>
	void ApplyGlobalVariable() override;
	/// <summary>
	/// スクリーンの作成
	/// </summary>
	void CreateScreen();

	static const Vector3 kScale; // スクリーンの固定スケール
	float scale_ = 1.0f; // スケール
	
	std::unique_ptr<Model> screen_; // スクリーン用板ポリ
	std::unique_ptr<Sprite> screenSprite_; // スクリーンの目用
	std::unique_ptr<PostEffect> postEffect_; // ポストエフェクト

	std::unique_ptr<PostEffect> postEffect1_; // ポストエフェクト2

	std::unique_ptr<Camera> camera_; // カメラ
};
