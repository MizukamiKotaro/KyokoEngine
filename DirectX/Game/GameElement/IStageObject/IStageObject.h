#pragma once
#include "Editor/StageEditor.h"
class Camera;
class InstancingModelManager;
class InstancingMeshTexData;

class IStageObject
{
public:
	static void StaticInitialize();
	virtual ~IStageObject() = default;
	virtual void Initialize();
	virtual void Update(const float& deltaTime = 0) = 0;
	virtual void SetTime(const float& time);
	virtual void Draw(const Camera& camera) = 0;
	virtual void DrawLight(const Camera& camera);
	virtual void DrawOutline(const Camera& camera);
	virtual void DrawBloom(const Camera& camera);

protected:
	void CreateStageEditor(const std::string& mainName, const std::string& name, const uint32_t& no, const bool& isMany = false);
	void CreateStageEditor(const std::string& mainName, const std::string& name, const std::string& treeName, const uint32_t& no, const bool& isMany = false);
	void InitializeEditor();
	void UpdateGlobalVariable();
	virtual void SetGlobalVariable() = 0;
	virtual void ApplyGlobalVariable() = 0;

	std::unique_ptr<StageEditor> stageEditor_;
	static InstancingModelManager* instancingManager_;
	const InstancingMeshTexData* instancingData_;
};