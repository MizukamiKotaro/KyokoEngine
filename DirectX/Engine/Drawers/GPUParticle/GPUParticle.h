#pragma once
#include "IParticle.cpp/IParticle.h"

class GPUParticle : public IParticle
{
public:
	GPUParticle(const std::string& particleName, const std::string& textureName, bool isStageEditor = false, BlendMode blendMode = BlendMode::kBlendModeNormal);
	GPUParticle(const std::string& particleName, const std::string& modelName, const std::string& textureName, bool isStageEditor = false, BlendMode blendMode = BlendMode::kBlendModeNormal);

	void Initialize();

	void Update(float deltaTime, Camera* camera);

	void Draw(Camera* camera);

private:
	void SetGlobalVariable() override;

	void ApplyGlobalVariable() override;



};