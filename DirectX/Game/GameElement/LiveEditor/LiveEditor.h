#pragma once
#include <memory>
#include <array>
#include "GameElement/IStageObject/IStageObjectManager.h"
#include "MultipleScreenEditor/MultipleScreenEditor.h"
#include "SpotLightAndOutline/SpotLightAndOutline.h"
#include "MMD/CameraVMD/CameraVMDAnimation.h"

class InstancingModelManager;

class LiveEditor {
public: 

	LiveEditor(Camera* camera);

	void Initialize();

	void Update(const float& time);

	void Draw();

	// スクリーンに書き出す
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
	std::unique_ptr<IStageObject> floor_;
	std::unique_ptr<IStageObject> dome_;

	std::map<uint32_t, std::unique_ptr<ScreenEditor>>* screenMap_ = nullptr;
	std::map<uint32_t, std::unique_ptr<SpotLightAndOutline>>* lightAndOutlineMap_ = nullptr;

	std::unique_ptr<SpotLightAndOutline> lightAndOutline_;
	Camera* camera_ = nullptr;
	std::unique_ptr<Camera> screenCamera_;
	std::unique_ptr<CameraVMDAnimation> cameraAnim_;
	float debugTime_;
	bool isDebug_;
};
