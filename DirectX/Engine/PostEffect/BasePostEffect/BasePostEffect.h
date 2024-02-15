#pragma once

#include <wrl.h>
#include <d3d12.h>
#include <stdint.h>
#include <string>
#include "Utils/Math/Vector2.h"
#include "Utils/Math/Vector4.h"
#include "Utils/Math/Matrix4x4.h"

#include "GraphicsPipelines/BlendModeConfig.h"

class DescriptorHandles;
enum class PipelineType;
class GraphicsPipelineManager;
class DescriptorHeap;

class BasePostEffect
{
public:
	
	virtual ~BasePostEffect();

	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	static void StaticInitialize();

	virtual void Initialize();

	virtual void Update();

	virtual void Draw(BlendMode blendMode = BlendMode::kBlendModeNormal);

	void PreDrawScene();

	void PostDrawScene();


protected:
	void PreDraw() const;

	virtual void CreateResources();

public:

	const D3D12_GPU_DESCRIPTOR_HANDLE GetSRVGPUDescriptorHandle() const;

protected:

	struct VertexData
	{
		Vector4 vertexPos;
		Vector2 texcoord;
	};

	struct Material
	{
		Vector4 color;
		Matrix4x4 uvTransform;
	};

	struct TransformationMatrix {
		Matrix4x4 WVP;
	};

	void SetAnchorPoint(const Vector2& anchorpoint);

	void SetColor(const Vector4& color);

	void SetTextureTopLeft(const Vector2& texTopLeft);

	void SetTextureSize(const Vector2& texSize);

	void TransferSize();

	void TransferUV();

	void CreatePostEffect();

private:

	void CreateVertexRes();

	void CreateMaterialRes();

	void CreateTranformRes();

	void CreateTexRes();

	void CreateRTV();

	void CreateDSV();


protected:

	ComPtr<ID3D12Resource> vertexResource_;
	VertexData* vertexData_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};

	ComPtr<ID3D12Resource> materialResource_;
	Material* materialData_;

	ComPtr<ID3D12Resource> transformResource_;
	TransformationMatrix* transformData_;

	ComPtr<ID3D12Resource> texResource_;
	const DescriptorHandles* srvHandles_;

	ComPtr<ID3D12Resource> rtvResource_;
	const DescriptorHandles* rtvHandles_;

	ComPtr<ID3D12Resource> dsvResource_;
	const DescriptorHandles* dsvHandles_;

protected:

	static GraphicsPipelineManager* gpoManager_;
	static DescriptorHeap* srvHeap_;
	static DescriptorHeap* rtvHeap_;
	static DescriptorHeap* dsvHeap_;
	static ID3D12GraphicsCommandList* commandList_;

	PipelineType piplineType_;

	static const float clearColor[4];

	Matrix4x4 worldMat_;

	float rotate_;
	Vector2 pos_;
	Vector2 size_;

	Vector2 uvTranslate_;
	Vector2 uvScale_;
	float uvRotate_;

	Vector4 color_;

	Vector2 anchorPoint_;

	Vector2 textureLeftTop_;

	Vector2 textureSize_;

	bool isInvisible_ = false;
};

