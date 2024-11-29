#pragma once
#include "MMD/PMDModel/PMDModel.h"
#include "GameElement/BaseStageObject/BaseStageObject.h"
#include <memory>
/// <summary>
/// アイドルのエディター
/// </summary>
class DancingIdolEditor : public BaseStageObject
{
public: 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="mainName">メインの名前</param>
	/// <param name="name">名前</param>
	/// <param name="no">ナンバー</param>
	DancingIdolEditor(const std::string& mainName, const std::string& name, uint32_t no);
	/// <summary>
	/// 時間のセット
	/// </summary>
	/// <param name="time">時間</param>
	void SetTime(float time) override;
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

private:
	/// <summary>
	/// グローバル変数の設定
	/// </summary>
	void SetGlobalVariable() override;
	/// <summary>
	/// グローバル変数の適用
	/// </summary>
	void ApplyGlobalVariable() override;
	
	std::unique_ptr<PMDModel> idol_; // アイドル
	Vector3 firstPosition_; // 初期座標
};
