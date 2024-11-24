#pragma once
#include <memory>
#include <array>
#include "GameElement/IStageObject/IStageObjectManager.h"
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
	LiveEditor() = default;

	void WriteOutline();
	void Draw(std::unique_ptr<SpotLightAndOutline>& lightAndOutline, const Camera& camera);

private:
	enum ManagerNames
	{
		kLight,
		kIdol,
		kFire,
		kObject,
		kManagerEnd,
	};

	InstancingModelManager* instancingManager_;

	std::array<std::unique_ptr<IStageObjectManager>, ManagerNames::kManagerEnd> objectManagers_;

	std::unique_ptr<MultipleScreenEditor> screenManager_;

	std::map<uint32_t, std::unique_ptr<ScreenEditor>>* screenMap_ = nullptr;
	std::map<uint32_t, std::unique_ptr<SpotLightAndOutline>>* lightAndOutlineMap_ = nullptr;

	std::unique_ptr<SpotLightAndOutline> lightAndOutline_;
	Camera* camera_ = nullptr;
	std::unique_ptr<Camera> screenCamera_;
	std::unique_ptr<CameraVMDAnimation> cameraAnim_;
	float debugTime_;
	float preDebugTime_;
	bool isDebug_;
};
