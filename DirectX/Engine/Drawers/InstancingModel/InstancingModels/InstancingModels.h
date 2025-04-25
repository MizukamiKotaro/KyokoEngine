#pragma once
#include <list>

#include "Light/Light.h"
#include "Drawers/DrawerBase/DrawerBase.h"
#include "ModelData/ModelData.h"
#include "Descriptor/DescriptorHandles/DescriptorHandles.h"

#include "InstancingModelData.h"

class Camera;
enum class PipelineType;
class BaseLight;
class InstancingResourceManager;
/// <summary>
/// インスタンシング用のインスタンス
/// </summary>
class Instance : public DrawerBase
{
public:
	static const uint32_t kNumInstance = 10000; // インスタンスの数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="modelData">グループデータ</param>
	Instance(const InstancingGroupData* modelData);
	~Instance();

	void Draw(const Camera& camera, std::list<InstancingModelData>& blocks, const InstancingGroupData* modelData);
	void Draw(const Camera& camera, std::list<InstancingModelData>& blocks, const std::string& tag);

	static void PreDraw();

	void SetMesh(const InstancingGroupData* modelData);

	void SetLight(const BaseLight* light);

private:
	void Draw(const Camera& camera, std::list<InstancingModelData>& blocks);

private:
	InstancingResourceManager* resourceManager_;

	Light light_;

private:

	static const PipelineType pipelineType_;
	const InstancingGroupData* modelData_;
};