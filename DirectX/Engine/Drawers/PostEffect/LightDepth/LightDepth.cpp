#include "LightDepth.h"

#include "Engine/Base/DirectXBase/DirectXBase.h"
#include "Engine/Base/DescriptorHeapManager/DescriptorHeapManager.h"
#include "Camera.h"
#include "GraphicsPipelineSystem/PipelineTypeConfig.h"
#include "DescriptorHeapManager/DescriptorHandles/DescriptorHandles.h"
#include "DescriptorHeapManager/DescriptorHeap/DescriptorHeap.h"
#include "GraphicsPipelineSystem/GraphicsPiplineManager/GraphicsPiplineManager.h"
#include "Externals/DirectXTex/d3dx12.h"
#include "ResourceManager/ResourceManager.h"

LightDepth::LightDepth(const Vector2& size)
{
	piplineType_ = PipelineType::LIGHT_DEPTH;
	outlineData_ = nullptr;
	CreatePostEffect(true, true, size);
}

LightDepth::~LightDepth()
{
	ResourceManager::GetInstance()->AddReleaseResource(std::move(outlineResource_));
	srvHeap_->AddDeleteDescriptor(depthHandles_);
}

void LightDepth::Draw(BlendMode blendMode)
{
	materialData_->color = color_;

	PreDraw();

	psoManager_->SetBlendMode(piplineType_, blendMode);

	ToReadBarrier();

	commandList_->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());
	commandList_->SetGraphicsRootDescriptorTable(1, srvHandles_->gpuHandle);
	commandList_->SetGraphicsRootConstantBufferView(2, outlineResource_->GetGPUVirtualAddress());
	commandList_->SetGraphicsRootDescriptorTable(3, depthHandles_->gpuHandle);
	commandList_->SetGraphicsRootDescriptorTable(4, outlineTex_);
	commandList_->SetGraphicsRootDescriptorTable(5, outlineDepth_->gpuHandle);
	commandList_->SetGraphicsRootDescriptorTable(6, objectTex_);
	commandList_->SetGraphicsRootDescriptorTable(7, objectDepth_->gpuHandle);
	commandList_->SetGraphicsRootDescriptorTable(8, bloomTex_);
	commandList_->SetGraphicsRootDescriptorTable(9, bloomDepth_->gpuHandle);
	commandList_->DrawInstanced(3, 1, 0, 0);

	ToWriteBarrier();
}

void LightDepth::Draw(const Camera& camera, BlendMode blendMode)
{
	materialData_->color = color_;
	outlineData_->projectionInverse = camera.GetInverseProjection();

	PreDraw();

	psoManager_->SetBlendMode(piplineType_, blendMode);

	ToReadBarrier();

	commandList_->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());
	commandList_->SetGraphicsRootDescriptorTable(1, srvHandles_->gpuHandle);
	commandList_->SetGraphicsRootConstantBufferView(2, outlineResource_->GetGPUVirtualAddress());
	commandList_->SetGraphicsRootDescriptorTable(3, depthHandles_->gpuHandle);
	commandList_->SetGraphicsRootDescriptorTable(4, outlineTex_);
	commandList_->SetGraphicsRootDescriptorTable(5, outlineDepth_->gpuHandle);
	commandList_->SetGraphicsRootDescriptorTable(6, objectTex_);
	commandList_->SetGraphicsRootDescriptorTable(7, objectDepth_->gpuHandle);
	commandList_->SetGraphicsRootDescriptorTable(8, bloomTex_);
	commandList_->SetGraphicsRootDescriptorTable(9, bloomDepth_->gpuHandle);
	commandList_->DrawInstanced(3, 1, 0, 0);

	ToWriteBarrier();
}

void LightDepth::ToReadBarrier()
{
	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(dsvResource_.Get(),
		D3D12_RESOURCE_STATE_DEPTH_WRITE, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
	commandList_->ResourceBarrier(1, &barrier);
}

void LightDepth::ToWriteBarrier()
{
	CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(dsvResource_.Get(),
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_DEPTH_WRITE);
	commandList_->ResourceBarrier(1, &barrier);
}

void LightDepth::CreateOutlineRes()
{
	outlineResource_ = DirectXBase::CreateBufferResource(sizeof(OutlineData));
	outlineResource_->Map(0, nullptr, reinterpret_cast<void**>(&outlineData_));
	outlineData_->projectionInverse = Matrix4x4::MakeIdentity4x4();
	outlineData_->lengthChange = 75.0f;
	outlineData_->maxWidth = 7;
	outlineData_->maxLength = 1000.0f;
}

void LightDepth::CreateDepthRes()
{
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;
	depthHandles_ = srvHeap_->GetNewDescriptorHandle();

	device_->CreateShaderResourceView(dsvResource_.Get(), &srvDesc, depthHandles_->cpuHandle);
}

void LightDepth::CreateResources()
{
	BasePostEffect::CreateResources();
	CreateOutlineRes();
	CreateDepthRes();
}
