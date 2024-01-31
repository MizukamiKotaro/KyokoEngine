#pragma once

#include <wrl.h>
#include <d3d12.h>
#include <stdint.h>
#include <string>
#include "Utils/Math/Vector2.h"
#include "Utils/Math/Vector4.h"
#include "Utils/Math/Matrix4x4.h"
#include "GraphicsPipelines/GraphicsPiplineManager/GraphicsPiplineManager.h"
#include "DescriptorHeapManager/DescriptorHeap/DescriptorHeap.h"

// スプライト
class PostEffect
{
public:

	PostEffect();
	
	virtual ~PostEffect();

	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	virtual void Initialize();

	virtual void Update();

	virtual void Draw(BlendMode blendMode = BlendMode::kBlendModeNormal);


	void PreDrawScene();

	void PostDrawScene();


protected:
	void PreDraw() const { GraphicsPiplineManager::GetInstance()->PreDraw(piplineType_); }

	virtual void CreateResources();

public:

	const D3D12_GPU_DESCRIPTOR_HANDLE GetSRVGPUDescriptorHandle() const { return srvHandles_->gpuHandle; };

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
		//Matrix4x4 World;
	};

	void SetAnchorPoint(const Vector2& anchorpoint);

	void SetColor(const Vector4& color);

	void SetTextureTopLeft(const Vector2& texTopLeft);

	void SetTextureSize(const Vector2& texSize);

	void TransferSize();

	void TransferUV();

	void CreateVertexRes();

	void CreateMaterialRes();

	void CreateTranformRes();

	void CreateTexRes();

	void CreateRTV();

	void CreateDSV();

	void CreatePostEffect();

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

	GraphicsPiplineManager::PiplineType piplineType_;

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

