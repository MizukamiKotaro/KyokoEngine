#pragma once
#include "../GPUParticleData.h"
#include <memory>
#include "Drawers/IDrawer/IDrawer.h"
#include "Editor/StageEditor.h"

class Camera;

class IParticle : public IDrawer
{
public:
	
	static void StaticInitialize();

	void Initialize();

	void Update(float deltaTime, Camera* camera);

	void Draw(Camera* camera);

protected:
	void CreateParticle(const std::string& particleName, const std::string& textureName, bool isStageEditor = false, BlendMode blendMode = BlendMode::kBlendModeNormal);
	void CreateParticle(const std::string& particleName, const std::string& modelName, const std::string& textureName, bool isStageEditor = false, BlendMode blendMode = BlendMode::kBlendModeNormal);

	virtual void SetGlobalVariable() = 0;

	virtual void ApplyGlobalVariable() = 0;

protected:
	static const ModelData* plane_;
	GPUParticleMeshTexData drawData_;

	std::unique_ptr<GlobalVariableUser> globalVariable_;
	std::unique_ptr<StageEditor> stageEditor_;

};