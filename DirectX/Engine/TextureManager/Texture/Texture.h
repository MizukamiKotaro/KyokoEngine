#pragma once

#include <wrl.h>
#include <d3d12.h>
#include <string>
#include "Externals/DirectXTex/DirectXTex.h"
#include "DescriptorHeapManager/DescriptorHeap/DescriptorHeap.h"

template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

struct Texture {
	ComPtr<ID3D12Resource> resource_;
	ComPtr<ID3D12Resource> intermediateResource_;
	const DescriptorHandles* handles_;
	std::string filePath_;
};