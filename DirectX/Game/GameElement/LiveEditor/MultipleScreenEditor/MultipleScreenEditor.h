#pragma once
#include <memory>
#include "Sprite.h"
#include "PostEffect/PostEffect.h"
#include "Bloom/Bloom.h"
#include <map>
#include "GameElement/BaseStageObject/BaseStageObject.h"
#include "SpotLightAndOutline/SpotLightAndOutline.h"

class ScreenEditor;
/// <summary>
/// 複数スクリーンエディター
/// </summary>
class MultipleScreenEditor : public BaseStageObject
{
public: 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="mainName">メインの名前</param>
	/// <param name="name">名前</param>
	/// <param name="no">ナンバー</param>
	MultipleScreenEditor(const std::string& mainName, const std::string& name, uint32_t no);
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
	/// スクリーン数の取得、現在は同じスクリーン画面になるようにしているため１を返す
	/// </summary>
	/// <returns>スクリーン数</returns>
	uint32_t GetScreenNum() { return 1; }
	/// <summary>
	/// スクリーンのマップの取得
	/// </summary>
	/// <returns>スクリーンのマップ</returns>
	std::map<uint32_t, std::unique_ptr<ScreenEditor>>* GetScreenMap() { return &screenMap_; }
	/// <summary>
	/// ポストエフェクトのマップの取得
	/// </summary>
	/// <returns>ポストエフェクトのマップ</returns>
	std::map<uint32_t, std::unique_ptr<SpotLightAndOutline>>* GetOutlineMap() { return &lightAndOutlineMap_; }

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

private:
	uint32_t screenNum_ = 1; // スクリーン数

	std::map<uint32_t, std::unique_ptr<ScreenEditor>> screenMap_; // スクリーンのマップ
	std::map<uint32_t, std::unique_ptr<SpotLightAndOutline>> lightAndOutlineMap_; // ポストエフェクトのマップ
	/// <summary>
	/// ツリーの名前
	/// </summary>
	struct TreeNames
	{
		std::string main; // メイン
		std::string name; // 名前
		std::string tree; // ツリー
	};
	std::unique_ptr<TreeNames> treeName; // ツリーの名前
};
