#pragma once
#include "IParticle.cpp/IParticle.h"
#include <wrl.h>
#include <d3d12.h>

namespace Kyoko {
	namespace Descriptor {
		class DescriptorHandles;
	}
}

class GPUParticle : public IParticle
{
public:
	GPUParticle(const std::string& particleName, const std::string& textureName, bool isStageEditor = false);
	~GPUParticle();

	void Initialize() override;

	void Update(const float& deltaTime) override;

	void Draw(const Camera& camera, const BlendMode& blend = BlendMode::kBlendModeNormal) override;

	const D3D12_GPU_DESCRIPTOR_HANDLE& GetParticleGPUDescriptorHandle() const;

private:
	void SetGlobalVariable() override;

	void ApplyGlobalVariable() override;

	const Kyoko::Descriptor::DescriptorHandles* particleUAVHandle_;
	const Kyoko::Descriptor::DescriptorHandles* particleSRVHandle_;
	Microsoft::WRL::ComPtr<ID3D12Resource> particleResouce_;

};