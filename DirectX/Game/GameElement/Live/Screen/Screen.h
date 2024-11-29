#pragma once
#include "Model.h"
#include <memory>
#include "Sprite.h"
#include "PostEffect/PostEffect.h"
#include "Bloom/Bloom.h"
#include "GlobalVariables/GlobalVariableUser.h"

class Camera;

/// <summary>
/// スクリーン
/// </summary>
class Screen {
public: 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Screen();
	/// <summary>
	/// グローバル変数を使用する場合のコンストラクタ
	/// </summary>
	/// <param name="chunkName">チャンク名</param>
	/// <param name="groupName">グループ名</param>
	Screen(const std::string& chunkName, const std::string& groupName);
	void Initialize();
	void Update();
	void Draw(Camera* camera);

	/// <summary>
	/// スクリーンに書き込み前処理
	/// </summary>
	void PreDrawScene();
	/// <summary>
	/// スクリーンに書き込み後処理
	/// </summary>
	void PostDrawScene();

public:
	/// <summary>
	/// スクリーンに映したいテクスチャのセット
	/// </summary>
	/// <param name="srvGPUDescriptorHandle">テクスチャ</param>
	void SetGPUHandle(D3D12_GPU_DESCRIPTOR_HANDLE srvGPUDescriptorHandle);
	/// <summary>
	/// テクスチャを書き込み式にリセット
	/// </summary>
	void Reset();

private:
	/// <summary>
	/// グローバル変数の設定
	/// </summary>
	void SetGlobalVariable();
	/// <summary>
	/// グローバル変数の適用
	/// </summary>
	void ApplyGlobalVariable();

private:

	static const Vector3 kScale; // スクリーンの幅固定用スケール
	float scale_ = 1.0f; // スケール
	
	std::unique_ptr<Model> screen_; // 板ポリ
	std::unique_ptr<Sprite> screenSprite_; // 網目スプライト
	std::unique_ptr<PostEffect> postEffect_; // ポストエフェクト
	std::unique_ptr<PostEffect> postEffect1_; // ポストエフェクト2
	std::unique_ptr<Bloom> bloom_; // ブルーム

	std::unique_ptr<GlobalVariableUser> globalVariable_; // グローバル変数使用
};
