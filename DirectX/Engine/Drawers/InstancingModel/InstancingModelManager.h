#pragma once
#include <list>
#include <unordered_map>
#include <memory>
#include "DescriptorHeapManager/DescriptorHeap/DescriptorHeap.h"
#include "Drawers/DrawerBase/DrawerBase.h"

#include "ModelData/ModelData.h"
#include "DescriptorHeapManager/DescriptorHandles/DescriptorHandles.h"
#include "ILight/ILight.h"

#include "InstancingModelData.h"
#include "InstancingModelList/InstancingModelList.h"

class Camera;

class InstancingModelManager : public DrawerBase
{
public:

	static InstancingModelManager* GetInstance();

	void FirstInitialize();

	void Draw(const Camera& camera, const InstancingGroupData* modelData);
	void Draw(const Camera& camera, const std::string& tag = "normal");

	const InstancingGroupData* GetDrawData(const InstancingGroupData& data);
	// 板ポリの場合
	const InstancingGroupData* GetDrawData(const std::string& texturePath, const std::string& tag = "normal", const BlendMode& blendMode = BlendMode::kBlendModeNormal);

	InstancingModelData* const AddBox(const InstancingGroupData* modelData, InstancingModelData&& model);

	void Clear();

	void SetLight(const InstancingGroupData* modelData, const ILight* light);

private:
	InstancingModelManager() = default;
	~InstancingModelManager() = default;
	InstancingModelManager(const InstancingModelManager&) = delete;
	const InstancingModelManager& operator=(const InstancingModelManager&) = delete;

private:
	std::unordered_map<const InstancingGroupData*, std::unique_ptr<InstancingModelList>> instancingModelMap_;
	std::list<std::unique_ptr<InstancingGroupData>> drawDatas_;
	const ModelData* plane_;
};