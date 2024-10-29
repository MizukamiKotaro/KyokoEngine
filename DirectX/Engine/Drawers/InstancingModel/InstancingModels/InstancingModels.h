#pragma once
#include <list>

#include "Light/Light.h"
#include "Drawers/IDrawer/IDrawer.h"
#include "ModelData/ModelData.h"
#include "DescriptorHeapManager/DescriptorHandles/DescriptorHandles.h"

#include "InstancingModelData.h"

class Camera;
enum class PipelineType;
class ILight;
class InstancingResourceManager;

class InstancingModels : public IDrawer
{
public:
	static const uint32_t kNumInstance = 10000;

	InstancingModels(const InstancingMeshTexData* modelData);
	~InstancingModels();

	void Draw(const Camera& camera, std::list<InstancingModelData>& blocks, const InstancingMeshTexData* modelData);
	void Draw(const Camera& camera, std::list<InstancingModelData>& blocks, const std::string& tag);

	static void PreDraw();

	void SetMesh(const InstancingMeshTexData* modelData);

	void SetLight(const ILight* light);

private:
	void Draw(const Camera& camera, std::list<InstancingModelData>& blocks);

private:
	InstancingResourceManager* resourceManager_;

	Light light_;

private:

	static const PipelineType pipelineType_;
	const InstancingMeshTexData* modelData_;
};