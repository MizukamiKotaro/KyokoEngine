#pragma once

#include <wrl.h>
#include <string>
#include "Drawers/DrawerBase/DrawerBase.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "Resource/Resource.h"

class Camera;
class Texture;

class Skybox : public DrawerBase
{
public:

	Skybox(const std::string& filename, const Vector3& scale = { 50.0f,50.0f,50.0f }, const Vector3& rotate = { 0.0f,0.0f,0.0f }, const Vector3& position = { 0.0f,0.0f,0.0f }, const Vector4& color = { 1.0f,1.0f,1.0f,1.0f });
	~Skybox();

	struct VertexData
	{
		Vector4 vertexPos;
	};
	struct Material
	{
		Vector4 color;
	};
	struct TransformationMatrix {
		Matrix4x4 WVP;
	};

	void Update();

	void Draw(const Camera& camera);

public:
	void LoadTexture(const std::string& filePath);
	void SetTexture(const Texture* texture);
	void SetColor(const Vector4& color);

private:
	void CreateVertexRes();
	void CreateMaterialRes();
	void CreateTranformRes();

private:
	Kyoko::ResourceManualRelease vertexResource_;
	VertexData* vertexData_;
	Kyoko::ResourceManualRelease indexResource_;
	D3D12_INDEX_BUFFER_VIEW indexBufferView_{};
	uint32_t* mappedIndex;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};
	Kyoko::ResourceManualRelease materialResource_;
	Material* materialData_;
	Kyoko::ResourceManualRelease transformResource_;
	TransformationMatrix* transformData_;

public:
	Vector3 scale_;
	Vector3 rotate_;
	Vector3 position_;

private:
	Matrix4x4 worldMat_;
	const Texture* texture_;
};

