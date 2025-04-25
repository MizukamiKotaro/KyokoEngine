#pragma once
#include <array>
#include <vector>
#include <span>
#include <wrl.h>
#include <d3d12.h>
#include "Matrix4x4.h"
#include "ModelData/VertexData3D.h"
#include "Descriptor/DescriptorHandles/DescriptorHandles.h"
#include "Resource/Resource.h"

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
struct SkinCluster
{
	std::vector<Matrix4x4> inverseBindPoseMatrices;
	Kyoko::ResourceManualRelease influenceResouce;
	std::span<VertexInfluence> mappedInfluence;
	Kyoko::ResourceManualRelease paletteResouce;
	std::span<WellForGPU> mappedPalette;
	const Kyoko::Descriptor::DescriptorHandles* paletteSrvHandle;

	const Kyoko::Descriptor::DescriptorHandles* inputVertexSrvHandle;
	Kyoko::ResourceManualRelease outputVertexResouce;
	const Kyoko::Descriptor::DescriptorHandles* outputVertexSrvHandle;
	const Kyoko::Descriptor::DescriptorHandles* influenceSrvHandle;
	Kyoko::ResourceManualRelease informationResouce;
	uint32_t* information;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	~SkinCluster();
};