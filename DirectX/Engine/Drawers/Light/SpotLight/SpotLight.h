#pragma once
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "ILight/ILight.h"
#include "GraphicsPipelineSystem/BlendModeConfig.h"

class Camera;
class ModelData;
class DrawLightManager;

class SpotLight : public ILight
{
public:
	struct SpotLightData
	{
		Vector4 color; // ライトの色
		Vector3 position; // 位置
		float intensity; // 輝度
		Vector3 direction; // スポットライトの方向
		float distance; // ライトの届く距離
		float decay; // 減衰率
		float cosAngle; // スポットライトの余弦
		float cosFalloffStart;
		float padding;
	};

	SpotLight();
	~SpotLight() override;

	static void StaticInitialize();

	void Update() override;

	void Draw(const Camera& camera, const BlendMode& blendMode = BlendMode::kBlendModeNormal) const;

public:
	SpotLightData* light_ = nullptr;
	bool isDraw_;

	static DrawLightManager* drawManager_;
};
