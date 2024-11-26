#pragma once
#include <memory>
#include <array>
#include "GameElement/BaseStageObject/StageObjectManager.h"
#include "MultipleScreenEditor/MultipleScreenEditor.h"
#include "SpotLightAndOutline/SpotLightAndOutline.h"
#include "MMD/CameraVMD/CameraVMDAnimation.h"

class InstancingModelManager;

/// <summary>
/// ライブエディター
/// </summary>
class LiveEditor {
public: 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="camera">カメラ</param>
	LiveEditor(Camera* camera);
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="time">デルタタイム</param>
	void Update(float time);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// スクリーンに書き込む
	/// </summary>
	void WriteScreen();

private:
	/// <summary>
	/// アウトラインとかの為に書き込む
	/// </summary>
	void WriteOutline();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="lightAndOutline">書き込み用</param>
	/// <param name="camera">カメラ</param>
	void Draw(std::unique_ptr<SpotLightAndOutline>& lightAndOutline, const Camera& camera);

private:
	/// <summary>
	/// マネージャーの名前
	/// </summary>
	enum ManagerNames
	{
		kLight, // ライト
		kIdol, // アイドル
		kObject, // オブジェクト
		kManagerEnd, // 名前の数
	};

	InstancingModelManager* instancingManager_; // インスタンシングマネージャー

	std::array<std::unique_ptr<StageObjectManager>, ManagerNames::kManagerEnd> objectManagers_; // マネージャー
	std::unique_ptr<MultipleScreenEditor> screenManager_; // スクリーンマネージャー

	std::map<uint32_t, std::unique_ptr<ScreenEditor>>* screenMap_ = nullptr; // スクリーンマップ
	std::map<uint32_t, std::unique_ptr<SpotLightAndOutline>>* lightAndOutlineMap_ = nullptr; // 専用ポストエフェクトマップ

	std::unique_ptr<SpotLightAndOutline> lightAndOutline_; // 専用ポストエフェクト
	Camera* camera_ = nullptr; // カメラ
	std::unique_ptr<Camera> screenCamera_; // スクリーン用カメラ
	std::unique_ptr<CameraVMDAnimation> cameraAnim_; // カメラアニメーション
	float debugTime_; // デバッグタイム
	float preDebugTime_; // 以前のデバッグタイム
	bool isDebug_; // デバッグか
};
