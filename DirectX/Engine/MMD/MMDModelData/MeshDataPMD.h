#pragma once

#include <vector>
#include <wrl.h>
#include "VertexDataPMD.h"
#include <d3d12.h>

struct MeshDataPMD
{
	std::vector<VertexDataPMD> verteces;
	std::vector<uint32_t> indices;
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_;
	Microsoft::WRL::ComPtr<ID3D12Resource> indexResource_;
	VertexDataPMD* vertexData_;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};
	D3D12_INDEX_BUFFER_VIEW indexBufferView_{};
	uint32_t* mappedIndex;
};