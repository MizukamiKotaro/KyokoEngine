#pragma once
#include <list>
#include <memory>

#include "InstancingModelData.h"
#include "InstancingModels/InstancingModels.h"
#include "ILight/ILight.h"

class Camera;

class InstancingModelList {
public:

	InstancingModelList(const InstancingGroupData* modelData);

	void Draw(const Camera& camera, const InstancingGroupData* modelData);
	void Draw(const Camera& camera, const std::string& tag);

public:

	void Clear();

	InstancingModelData* const AddModel(InstancingModelData&& instancingModel);

	uint32_t GetSize() const;

	void SetModel(const InstancingGroupData* modelData);

	void SetLight(const ILight* light);

private:

	std::unique_ptr<InstancingModels> modelsResource_;
	std::list<InstancingModelData> modelList_;
};