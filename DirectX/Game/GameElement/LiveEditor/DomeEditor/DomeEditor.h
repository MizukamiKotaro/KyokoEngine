#pragma once
#include "Model.h"
#include <memory>
#include "GameElement/BaseStageObject/BaseStageObject.h"

class DomeEditor : public BaseStageObject
{
public: 
	DomeEditor(const std::string& mainName, const std::string& name, uint32_t no);

	void Initialize() override;
	void Update(float time) override;
	void Draw(const Camera& camera) override;

private:
	void SetGlobalVariable() override;
	void ApplyGlobalVariable() override;
	
	std::unique_ptr<Model> model_;
};
