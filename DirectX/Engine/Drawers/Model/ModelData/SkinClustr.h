#pragma once
#include <array>
#include <vector>
#include <span>
#include <wrl.h>
#include <d3d12.h>
#include "Matrix4x4.h"
#include "Base/DescriptorHeapManager/DescriptorHandles/DescriptorHandles.h"

const uint32_t kNumMaxInfluence = 4;
struct VertexInfluence
{
	std::array<float, kNumMaxInfluence> weights;
	std::array<uint32_t, kNumMaxInfluence> jointIndices;
};
struct WellForGPU
{
	Matrix4x4 skeletonSpaceMatrix; // 位置用
	Matrix4x4 skeletonSpaceInverseTransposeMatrix; // 法線用
};
struct SkinCluter
{
	std::vector<Matrix4x4> inverseBindPoseMatrices;
	Microsoft::WRL::ComPtr<ID3D12Resource> influenceResouce;
	D3D12_VERTEX_BUFFER_VIEW influenceBufferView{};
	std::span<VertexInfluence> mappedInfluence;
	Microsoft::WRL::ComPtr<ID3D12Resource> paletteResouce;
	std::span<WellForGPU> mappedPalette;
	const DescriptorHandles* paletteSrvHandle;
};