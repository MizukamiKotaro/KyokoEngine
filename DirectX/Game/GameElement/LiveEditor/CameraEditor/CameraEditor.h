#pragma once
#include <memory>
#include "GameElement/BaseStageObject/BaseStageObject.h"

class CameraEditor : public BaseStageObject
{
public:
	CameraEditor(const std::string& mainName, const std::string& name, uint32_t no);

	void Initialize() override;
	void Update(float time) override;
	void Draw(const Camera& camera) override;

private:
	void SetGlobalVariable() override;
	void ApplyGlobalVariable() override;

	std::unique_ptr<Camera> camera_;

};