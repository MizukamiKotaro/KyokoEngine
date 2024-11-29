#pragma once
#include <list>
#include <memory>

#include "InstancingModelData.h"
#include "InstancingModels/InstancingModels.h"
#include "ILight/ILight.h"

class Camera;

/// <summary>
/// 
/// </summary>
class InstancingModelList {
public:

	InstancingModelList(const InstancingGroupData* modelData);

	void Draw(const Camera& camera, const InstancingGroupData* modelData);
	void Draw(const Camera& camera, const std::string& tag);

public:

	void Clear();

	void AddInstanceTransform(InstancingModelData&& instancingModel);

	uint32_t GetSize() const;

	void SetModel(const InstancingGroupData* modelData);

	void SetLight(const BaseLight* light);

private:

	std::unique_ptr<Instance> modelsResource_;
	std::list<InstancingModelData> modelList_;
};