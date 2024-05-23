#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include "ILight/ILight.h"
#include "Drawers/IDrawer/IDrawer.h"
#include <vector>
#include <memory>

class Camera;
class ModelData;
enum class BlendMode;
class PointLight;
class SpotLight;

class DrawLightManager : public IDrawer
{
public:
	static DrawLightManager* GetInstance();

	void Initialize();
	void Reset();

	void Draw(const PointLight& light,const Camera& camera, const BlendMode& blendMode);
	void Draw(const SpotLight& light, const Camera& camera, const BlendMode& blendMode);

private:
	DrawLightManager() = default;
	~DrawLightManager() = default;
	DrawLightManager(const DrawLightManager&) = delete;
	const DrawLightManager& operator=(const DrawLightManager&) = delete;

	class Transformation
	{
	public:
		Transformation();
		~Transformation();
		struct TransformationMatrix {
			Matrix4x4 WVP;
			Matrix4x4 World;
			Matrix4x4 WorldInverse;
		};
		Microsoft::WRL::ComPtr<ID3D12Resource> transformationResource;
		TransformationMatrix* transformationData;
	};
	std::vector<std::unique_ptr<Transformation>> transformation_;
	int32_t drawNum_;

	const ModelData* modelData_;
	Matrix4x4 scaleMat_;
	Matrix4x4 scaleInverseMat_;
};